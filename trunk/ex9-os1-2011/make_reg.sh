#!/bin/sh -x
echo "Start rpcgen operations"
rpcgen ex9_server.x
sed 's/_svc//g' ex9_server_svc.c > temp_ex9_serv
mv temp_ex9_serv ex9_server_svc.c
echo "Start compile Server"
gcc -Wall ex9_server_routines.c ex9_server_svc.c -lm -o server
echo "Start compile client"
gcc -Wall ex9_client_rpc.c ex9_server_clnt.c -o client
