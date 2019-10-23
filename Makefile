all:
	cc decode.c -o decode
	cc encode.c -o encode
	
decode:
	cc decode.c -o decode

encode:
	cc encode.c -o encode
	
clean:
	rm encode decode
