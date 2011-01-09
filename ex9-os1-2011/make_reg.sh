echo ""
echo "##################################################"
echo "Start rpcgen operation"
rpcgen ex9_server.x
echo "rpcgen operation complited"
echo "Replaicing _svc..."
sed 's/_svc//g' ex9_server_svc.c > temp_ex9_serv
mv temp_ex9_serv ex9_server_svc.c
echo "Start compile Server"
gcc -Wall ex9_server_routines.c ex9_server_svc.c -lm -o server
echo "Server complited the name for run ./server"
echo "Start compile Client"
gcc -Wall ex9_client_rpc.c ex9_server_clnt.c -o client
echo "Client complited the name for run ./client <host>"
echo "Complited."
echo "##################################################"
echo ""
