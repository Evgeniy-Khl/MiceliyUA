DIMENSION arData(9)
FOR  i=1 TO 9
	arData(i) = 48+i
ENDFOR 
lnNen = 1
lnCrc = 65535
lnXor = 0
DO WHILE lnNen < 10 	
	lnXor = arData(lnNen) *256
	lnCrc = BITXOR(lnXor,lnCrc)
	FOR  i=1 TO 8
		lnXor = BITAND(lnCrc,32768)
		IF lnXor > 0
			lnCrc = lnCrc*2
			lnCrc = BITAND(lnCrc,65535)
			lnCrc = BITXOR(4129,lnCrc)
		ELSE 
			lnCrc = lnCrc*2
			lnCrc = BITAND(lnCrc,65535)
		ENDIF  	
	ENDFOR
	lnNen = lnNen + 1 
ENDDO
SUSPEND
 

            
