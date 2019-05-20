// include mac / linux specific headers

int get_sockOpt(int handle, int option)
{
	int bufferSizeVal, result;
	socklen_t optLen = sizeof(bufferSizeVal);
	result = ::getsockopt(handle, SOL_SOCKET, option, (char *)&bufferSizeVal, &optLen);
	
	if(result < 0){
		cout << "Failed reading socket opt value" << endl;
	}
	else cout << "GET: Buff value: " << bufferSizeVal << "\tBuffer value size is: " << optLen << endl;
	
	return result;
}

int set_sockOpt(int handle, int option, int bufferSizeVal)
{
	int result;
	socklen_t optLen = sizeof(bufferSizeVal);
	result = ::setsockopt(handle, SOL_SOCKET, option, (char *)&bufferSizeVal, optLen);
	
	if(result < 0){
		cout << "Failed reading socket opt value" << endl;
	}
	else cout << "SET Buff value: " << bufferSizeVal << "\tBuffer value size is: " << optLen << endl;
	
	return result;
}

void sock_get_set_test()
{
	// cout << "in create socket file" << endl;
	
	int fd = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if(fd > 0)
		get_sockOpt(fd, SO_SNDBUF);
	
	if( set_sockOpt(fd, SO_SNDBUF, 65000) >= 0)
		cout << "Succeeded 65k set" << endl;
	
	get_sockOpt(fd, SO_SNDBUF);
	
	close(fd);
}

int main(int argc, const char * argv[]) {
		
	int i;
	for (i=0; i ; ++i)
		;
	cout << s.length() << endl;
	sock_get_set_test();
  
	return 0;
}
