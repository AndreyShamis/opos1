echo "Start compile Server"
gcc -Wall ex9_server_routines.c ex9_server_svc.c -lm -o server
echo "Start compile client"
gcc -Wall ex9_client_rpc.c ex9_server_clnt.c -o client
