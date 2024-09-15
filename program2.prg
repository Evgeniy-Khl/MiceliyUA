lnCrc = 65535
lnCrc = BITAND(lnCrc,32768)
IF lnCrc > 0
	lnCrc = lnCrc*2
	lnCrc = BITXOR(4129,lnCrc)
ELSE 
	lnCrc = lnCrc*2
ENDIF