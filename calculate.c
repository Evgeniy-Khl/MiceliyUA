unsigned char calcDj(signed int actualT)      // ��������� ������� �������� ������� � 1,2,3,4,5,6
{
 signed int err;
 unsigned char i,sw;
 static unsigned char outDj;
  for (i=0;i<8;i++)
   {
     sw = 2;
 
     err = faza[sys[0]].Dry;
     if(err) // ���� ������� �� ����� 0 �� �����������...
      {
        err = (err + digital[i].biasT) - actualT;
        if(digital[i].trend) err = -err;
        if(err > digital[i].bandT){sw = 0; outDj &= ~(1<<i);}; // ��������� (+x.xx ���.C.)
        if(err < 0) {sw = 1; outDj |= (1<<i);}                 // ��������    timerDj[i]
      }
     else sw = 0;// ����� ���������
     if(timerDj[i]>(digital[i].onTime-1+digital[i].offTime)) timerDj[i]=0;
     if(sw == 0)
      {
        if (timerDj[i]<digital[i].onTime) outDj |= (1<<i);  // ��������
        else  outDj &= ~(1<<i);                             // ���������
      };
   };
 return outDj;
}

void calcAn(signed int actualT)      // ��������� ������� ���������� ������� � 1,2,3,4
{
 signed int err;
 unsigned char i;
  for (i=0;i<6;i++)
   {
     /*
     switch (analog[i].sensor) // �������� ������� � ������������ � ������� ��������
      {
        case 1:  err = faza[stage].RH;  break;      // �������������� ���������
        case 2:  err = faza[stage].Soil; break;     // ����������� ��������
        case 3:  err = faza[stage].CO2;  break;     // ������ CO2
        case 4:  err = faza[stage].RHumidity; break;// ������ �������������� ���������
        default: err = faza[stage].Dry;
      };*/
     err = faza[sys[0]].Dry;
     if(err) // ���� ������� �� ����� 0 �� �����������...
      {
        err = (err + analog[i].biasT) - actualT;
        if(digital[i].trend) err = -err;
        if(err<=0) err = (int)analog[i].minVal;//*corrA/100;
        else if(err>=analog[i].bandT) err = (int)analog[i].maxVal;//*corrA/100;
        else {err *= 100; err /= analog[i].bandT;};// err *= corrA; err /= 100;
// ���� sys[1]=   0 �� �������� �����������! ���� sys[1]=100 �� ������� ������ �������!
// ���� corrA = 100 �� �������� �����������! ���� corrA =  0 �� ������� ������ �������!
        if(err < analog[i].minVal) err = analog[i].minVal;
      }
     else err = analog[i].minVal;// ����� ����������� ��������
     outU[i]=(char)err;
   };
}

void control(void)
{
 signed int actualT;
 actualT = Tf[0];                           // ������� �������� �������� ������� (3 ��.)
 if (actualT>maxT) maxT=actualT;
 if (actualT<minT) minT=actualT;
 calcAn(actualT);
 relay&=0xC0;
 relay|=calcDj(actualT);
 if (spT[1] - actualT < 0) error = 0x08;   // ����������� �������
 if (actualT - spT[2] < 0) error = 0x04;   // ����������� ������
}