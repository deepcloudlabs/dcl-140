/*
 * disconnect is passed a pointer to a Servlet
 * It should perform the following :
 *	1. Take the servlet out of the circular list
 *	3. Close the socket connection
 *	3. Set the closing time
 *	4. Create a Pending item and push the pending stack
 *	5. Alert the garbage collector 
 */

#include "sms.h"

void disconnect(Servlet * done) {
}
