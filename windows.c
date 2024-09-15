void windowMain(void)
{
 unsigned char i,x;
 signed int temp;
//-------------------------------- �������� ���������� ������������. ----------------------------------------------------------------------------
//-- ������ 1 ---------------------------
  lcd_clear(); 
  if(timerStop){lcd_putsf(str23); sprintf(lcd_buffer," %3i",timerStop); lcd_puts(lcd_buffer);}                          // ������ ��������� xx
  else if(timerDrying){lcd_putsf(menu42); sprintf(lcd_buffer," %3i",timerDrying); lcd_puts(lcd_buffer); lcd_putsf(st8);}// �������� xx ���.
  else if(error && (countTIM1_OVF & 4))
   {
    switch (error)
     {
      case 0x01: lcd_putsf(st7);lcd_putsf(st6);lcd_putsf(" Z1   "); break;// ������ ������a SPOT1
      case 0x02: lcd_putsf(st7);lcd_putsf(st6);lcd_putsf(" Z2   "); break;// ������ ������a SPOT2
      case 0x03: lcd_putsf(st7);lcd_putsf(st6);lcd_putsf(" Z12  "); break;// ������ ������a SPOT1+SPOT2
      case 0x04: lcd_putsf(st7);lcd_putsf(st6);lcd_putsf(" Z3   "); break;// ������ ������a SPOT3
      case 0x05: lcd_putsf(st7);lcd_putsf(st6);lcd_putsf(" Z13  "); break;// ������ ������a SPOT1+SPOT3
      case 0x06: lcd_putsf(st7);lcd_putsf(st6);lcd_putsf(" Z23  "); break;// ������ ������a SPOT2+SPOT3
      case 0x07: lcd_putsf(st7);lcd_putsf(st6);lcd_putsf(" Z123 "); break;// ������ ������a SPOT1+SPOT2+SPOT3
      case 0x08: lcd_putsf(st7);lcd_putsf(st6);lcd_putsf(" CO2  "); break;// ������ ������a CO2
      case 0x10: lcd_putsf(st7);lcd_putsf(st6);lcd_putsf(" DHT22"); break;// ������ ������a DHT22
      default:   lcd_putsf(st7);lcd_putsf(" �������� ��� �������");
     };
   }
  else
   {
    i = sys[0]; if(ChangeFaza & (countTIM1_OVF & 1)) x=0xDD; else x=0x20;
    read_clock(); lcd_putsf(str10);//����
    sprintf(lcd_buffer,"-%i%c %2x\xE3.%02x\xC0.%02x\xBC.",i+1,x,dayStage,clock_buffer[2],clock_buffer[1]);//����;����;���;���.
    lcd_puts(lcd_buffer);
   }

//-- ������ 2 ---------------------------
  lcd_gotoxy(0,1); lcd_putsf(ms0);// ����.
  temp = Tf[0];                   // ������ �������  z1[0]
  checksign(temp);                // �������� ����� �����������
  if(temp<850)
   {
    sprintf(lcd_buffer,"%c%2i.%i",signchar,tDryInt,tDry); lcd_puts(lcd_buffer);
    temp = setpoint.dry; checksign(temp); if(timerDrying) tDryInt += sys[4];// ������� ����.
    sprintf(lcd_buffer,"[%2i.%i]%c%�",tDryInt,tDry,flags.ratDry,flags.unevenT); lcd_puts(lcd_buffer);
   }
  else lcd_putsf(st7);            // ������

//-- ������ 3 ---------------------------
  lcd_gotoxy(0,2); lcd_putsf(ms1);// ����. 
  temp = Tf[2];                   // ������� �������� �������� ��������  z2[]
  checksign(temp);                // �������� ����� �����������
  if(temp<850)
   {
    sprintf(lcd_buffer,"%c%2i.%i",signchar,tDryInt,tDry); lcd_puts(lcd_buffer);
    temp = setpoint.soil; checksign(temp);// ������� ����.
    sprintf(lcd_buffer,"[%2i.%i]%c",tDryInt,tDry,flags.ratSoil); lcd_puts(lcd_buffer);    
   }
  else lcd_putsf(st7);            // ������

//-- ������ 4 ---------------------------
  lcd_gotoxy(0,3); lcd_putsf(ms2);// �����.
  x = setpoint.rh; if(timerDrying) x -= sys[5];
  if(pvRH<101){sprintf(lcd_buffer," %3i%%[%3i%%]%c",pvRH,x,flags.ratRH); lcd_puts(lcd_buffer);}
  else lcd_putsf(st7);  // ������
}

//-------------------------------- ��������� �������� � ������. ---------------------------------------------------------------------------------
void windowA1(void)
{
 signed int temp;
//-- ������ 1 --------------------------
  lcd_clear();
  temp = outU[0];
  lcd_putsf(ms3); sprintf(lcd_buffer,"%3i%% ",temp); lcd_puts(lcd_buffer);// ����.��
  switch (flags.vent)
   {
    case 1: lcd_putsf(ms1);lcd_putsf("\x23"); break;//"����.#" ������������ ����������� ������������� ����������� �������� � ���� "����������" � "�������"
    case 2: lcd_putsf("CO2 \xDA"); break;           //"CO2 |"  ������������ ����������� ���������� ��2
    case 3: lcd_putsf(ms0);lcd_putsf("\xDA"); break;//"����.|" ������������ ����������� ��� ��������� �����������
    case 4: lcd_putsf(ms2);lcd_putsf("\xDA"); break;//"����.|" ������������ ����������� ���������
    case 5: lcd_putsf(ms0);lcd_putsf("\xD9"); break;//"����.|" ������������ ���������� ������� ������� ����.
    case 6: lcd_putsf(ms0);lcd_putsf("\xDA"); break;//"����.|" ������������ ���������� ������� �������� ����.
    default:lcd_putsf(str11);lcd_putsf("MIN");// ���. MIN
   };
   
//-- ������ 2 --------------------------
  lcd_gotoxy(0,1);
  temp = outU[1];
  lcd_putsf(ms4); sprintf(lcd_buffer,"%3i%% ",temp); lcd_puts(lcd_buffer);// ����.��
  switch (flags.flap)
   {
    case 1: lcd_putsf("CO2 \xDA"); break;           //"CO2 |" ������������ ����������� ���������� ��2
    case 2: lcd_putsf(ms0);lcd_putsf("\xDA"); break;//"����.|" ������������ ����������� ��� ��������� �����������
    case 3: lcd_putsf(ms2);lcd_putsf("\xDA"); break;//"����.|" ������������ ����������� ���������   
    default:lcd_putsf(str11);lcd_putsf("MIN");// ���. MIN
   };

//-- ������ 3 -------------------------
  lcd_gotoxy(0,2);
  temp = outU[4];
  lcd_putsf(ms5); sprintf(lcd_buffer,"%3i%% ",temp); lcd_puts(lcd_buffer);// ���� ��
  if(flags.freez){lcd_putsf(str16);lcd_putsf("\x2A");}   // ������ ������������� !!!
  else if(temp>0){lcd_putsf(ms0);lcd_putsf("\xD9");}//"����.|"
  else {lcd_putsf(str11);lcd_putsf("MIN");}// ���. MIN
  
//-- ������ 4 -------------------------
  lcd_gotoxy(0,3);
  temp = outU[5];
  lcd_putsf(ms6); sprintf(lcd_buffer,"%3i%% ",temp); lcd_puts(lcd_buffer);// ���� X�
  switch (flags.cold)
   {
    case 1: lcd_putsf(ms0);lcd_putsf("\xDA"); break;//"����.|" ������������ ����������� ��� ��������� �����������
    case 2: lcd_putsf(ms2);lcd_putsf("\xDA"); break;//"����.|" ������������ ����������� ���������   
    default:lcd_putsf(str11);lcd_putsf("MIN");// ���. MIN
   };
}

//-------------------------------- ������� ��������. --------------------------------------------------------------------------------------------
void windowTz2(void)
{
 char i;
 signed int temp;
  lcd_clear();
  for (i=0;i<4;i++)
   {
    lcd_gotoxy(0,i);lcd_putsf(str17);lcd_putsf(ms1);lcd_gotoxy(11,i);sprintf(lcd_buffer,".%u",i); lcd_puts(lcd_buffer);  //������ ����.i 
    temp = z2[i];                          // ������ ��������  z2[]
    checksign(temp);                       // �������� ����� �����������
    if(temp==990) lcd_putsf(st7);          // ������
    else {sprintf(lcd_buffer,"  %c%2i.%i",signchar,tDryInt,tDry); lcd_puts(lcd_buffer);}
   };
}

//-------------------------------- ������ ��2 ---------------------------------------------------------------------------------------------------
void windowTz3(void)
{
 char i;
 signed int temp;
  lcd_clear();     lcd_putsf(str20); lcd_putsf(ms0);// ������ ����.
  lcd_gotoxy(0,1); lcd_putsf(str19); lcd_putsf(ms0);// �������� ����.
  lcd_gotoxy(0,2); lcd_putsf(str18); lcd_putsf(ms0);// �������� ����.     
  lcd_gotoxy(0,3); lcd_putsf("CO2,ppm ");
  for (i=0;i<4;i++)
   {
    temp = z3[i];                          // ������ ���� 3  z3[]
    checksign(temp);                       // �������� ����� ����������� 
    if(i<3)                                // ������ ��� �������� �����������
     {
      if(temp<850){sprintf(lcd_buffer,"%c%2i.%i",signchar,tDryInt,tDry); lcd_gotoxy(15,i); lcd_puts(lcd_buffer);}
      else {lcd_gotoxy(8,i); lcd_putsf(st7);}// ������
     }
    else
     {
      temp = setpoint.co2;
      if(CO2module){sprintf(lcd_buffer,"[%4i]%c %4i",temp,flags.ratCO2,Tf[3]); lcd_gotoxy(8,i); lcd_puts(lcd_buffer);}
      else {lcd_gotoxy(8,i); lcd_putsf(st7);}// ������
     };
   };
}