/**
 * Mysql plug in derived from C++ version of the xxhash hashing library.
 *
 * @author Tevfik KIZILOREN
 * @version $Revision: 1 $
 */

#ifdef STANDARD
#include <string.h>
#ifdef __WIN__
typedef unsigned __int64 ulonglong;
typedef __int64 longlong;
#else
typedef unsigned long long ulonglong;
typedef long long longlong;
#endif /*__WIN__*/
#else
#include <my_global.h>
#include <my_sys.h>
#endif
#include <mysql.h>
#include <m_ctype.h>
#include <m_string.h>
#include "xxhash64.h"

#ifdef HAVE_DLOPEN

extern "C" {
  my_bool  xxhash_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
  void xxhash_deinit(UDF_INIT *initid);
  longlong xxhash(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);
}

/**
 * Called once for each SQL statement which invokes xxhash();
 * checks arguments, sets restrictions, allocates memory that
 * will be used during the main xxhash() function (the same
 * memory will be reused for each row returned by the query).
 *
 * Takes a pointer to UDF_INIT struct which is to be shared with all
 * other functions defined here. The components of this struct are described
 * in the MySQL manual; pointer to UDF_ARGS struct which contains information
 * about the number, size, and type of args the query will be providing
 * to each invocation of xxhash(); pointer to a char
 * array of size MYSQL_ERRMSG_SIZE in which an error message
 * can be stored if necessary
 *
 * @return 1 for failure; 0 for successful initialization
 */
my_bool xxhash_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  // Make sure user provided 1 string argument
  if (args->arg_count != 1 || args->arg_type[0] != STRING_RESULT) {
    strcpy(message, "XXHASH() requires one string argument");
    return 1;
  }
  // Returns up to 20 digits, i.e. ceil(log(2^64)/log(10))
  initid->max_length = 20;
  initid->maybe_null = 0;
  return 0;
}

/**
 * Deallocate memory allocated by xxhash_init(); this function
 * is called once for each query which invokes xxhash(),
 * it is called after all of the calls to xxhash() are done.
 *
 * Takes pointer to UDF_INIT struct (the same which was used by
 * xxhash_init() and xxhash())
 */
void xxhash_deinit(UDF_INIT *initid) {
}

/**
 * Returns a 64 bit hash of the given string. This hash function
 * exhibits better statistical behavior than String hashCode() and
 * has speed comparable to CRC32.
 *
 * @param in string to checksum (should not be null)
 * @return a hash
 */
static longlong xxHash(const char *in, longlong length) {
  longlong result = (longlong)XXHash64::hash(in, length, 0);  
  return result;
}

/**
 * Compute the Irvine hash of a string.
 *
 * Takes a pointer to UDF_INIT struct which contains pre-allocated memory
 * in which work can be done; pointer to UDF_ARGS struct which 
 * contains the functions arguments and data about them; pointer
 * to mem which can be set to 1 if the result is NULL; pointer
 * to mem which can be set to 1 if the calculation resulted in an error.
 *
 * @return Irvine hash of the string.
 */
longlong xxhash(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error) {
  const char *s = args->args[0];
  longlong length = args->lengths[0];

  if (s == NULL) {
    return 0;
  } else {
    return xxHash(s, length);
  }
}

#endif /* HAVE_DLOPEN */
