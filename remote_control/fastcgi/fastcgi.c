/*
 * =====================================================================================
 *
 *       Filename:  fastcgi.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/28/2013 05:58:46 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <alloca.h>
#include <fcgiapp.h>
#define LISTENSOCK_FILENO 0
#define LISTENSOCK_FLAGS 0
int main(int argc, char** argv) {
  openlog("testfastcgi", LOG_CONS|LOG_NDELAY, LOG_USER);
  int err = FCGX_Init(); /* call before Accept in multithreaded apps */
  if (err) { syslog (LOG_INFO, "FCGX_Init failed: %d", err); return 1; }
  FCGX_Request cgi;
  err = FCGX_InitRequest(&cgi, LISTENSOCK_FILENO, LISTENSOCK_FLAGS);
  if (err) { syslog(LOG_INFO, "FCGX_InitRequest failed: %d", err); return 2; }

  while (1) {
    err = FCGX_Accept_r(&cgi);
    if (err) { syslog(LOG_INFO, "FCGX_Accept_r stopped: %d", err); break; }
    char** envp;
    int size = 200;
    for (envp = cgi.envp; *envp; ++envp) size += strlen(*envp) + 11;
    char*  result = (char*) alloca(size);
    strcpy(result, "Status: 200 OK\r\nContent-Type: text/html\r\n\r\n");
    strcat(result, "<html><head><title>testcgi</title></head><body><ul>\r\n");

    for (envp = cgi.envp; *envp; ++envp) {
      strcat(result, "<li>"); 
      strcat(result, *envp); 
      strcat(result, "</li>\r\n");
    }

    strcat(result, "</ul></body></html>\r\n");
    FCGX_PutStr(result, strlen(result), cgi.out);
  }

  return 0;
}
