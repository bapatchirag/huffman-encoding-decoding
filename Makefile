all:
	cc decode.c -o decode
	cc encode.c -o encode
	
decode:
	echo > ptext
	cc decode.c -o decode

encode:
	echo > etext
	cc encode.c -o encode
	
clean:
	rm encode decode
	
clean-text:
	echo > ptext
	echo > etext
