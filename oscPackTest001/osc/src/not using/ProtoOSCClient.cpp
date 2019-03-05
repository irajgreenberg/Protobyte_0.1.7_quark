#include "ProtoOSCClient.h"

char testdata[6] = "ABCDE";

int initClient(int argc, char *argv[])
{
    /* build a blob object from some data */
    lo_blob btest = lo_blob_new(sizeof(testdata), testdata);

    /* an address to send messages to. sometimes it is better to let the server
     * pick a port number for you by passing NULL as the last argument */
    lo_address t = lo_address_new(NULL, "7770");

    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'q') {
      /* send a message with no arguments to the path /quit */
      lo_send(t, "/quit", NULL);
    } else {
      /* send a message to /foo/bar with two float arguments, report any
       * errors */
      if (lo_send(t, "/foo/bar", "ff", 0.12345678f, 23.0f) == -1) {
	printf("OSC error %d: %s\n", lo_address_errno(t), lo_address_errstr(t));
      }

      /* send a message to /a/b/c/d with a mixtrure of float and string
       * arguments */
      lo_send(t, "/a/b/c/d", "sfsff", "one", 0.12345678f, "three",
	      -0.00000023001f, 1.0);

      /* send a 'blob' object to /a/b/c/d */
      lo_send(t, "/a/b/c/d", "b", btest);

      /* send a jamin scene change instruction with a 32bit integer argument */
      lo_send(t, "/jamin/scene", "i", 2);
    }

    return 0;
}