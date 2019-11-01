all:
	gcc decode.c -o decode
	gcc encode.c -o encode
	
decode:
	echo > ptext
	gcc decode.c -o decode

encode:
	echo > etext
	gcc encode.c -o encode
	
clean:
	rm encode decode
	
clean-text:
	echo > ptext
	echo > etext
