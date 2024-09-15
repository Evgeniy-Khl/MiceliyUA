void touchpad(char byte){
  char i, fz=sys[0];
     switch (displ_num){
        //-------------------------------------------------------------------------------- ����� -
        case 0: if(byte<buttonCount){displ_num = byte; newSetButt = 1;} break;
        //-------------------------------------------------------------------- ������ ���������� -
        case 1: if(byte<buttonCount){displ_num = byte; newSetButt = 1;} break; 
        case 2: //--------------------------------------------------- ��������� ��� <����� ������> ---------------------------------------------------------
          switch (byte){
            case 0: displ_num = 0; newSetButt = 1; break;
            case 1: if (--numMenu<0) numMenu = MAX_FAZA-1;    break;
            case 2: if (++numMenu>MAX_FAZA-1) numMenu = 0;    break;
            case 3: 
                    displ_num = numMenu+4; newSetButt = 1; 
                    switch (numMenu){
                        case 0:
                            newval[0] = faza[fz].Dry;
                            newval[1] = faza[fz].Soil;
                            newval[2] = faza[fz].RH;
                            newval[3] = faza[fz].CO2;
                        break;
                        case 1:
                            newval[0] = faza[fz].DeltaDry;
                            newval[1] = faza[fz].DeltaSoil;
                            newval[2] = faza[fz].DeltaRH;
                            newval[3] = faza[fz].DeltaCO2;
                        break;
                        case 2:
                            newval[0] = faza[fz].EnableDry;
                            newval[1] = faza[fz].EnableSoil;
                            newval[2] = faza[fz].EnableRH;
                            newval[3] = faza[fz].EnableCO2;
                        break;
                        case 3: for (i=0;i<4;i++) {newval[i] = autoA[i];} break;
                        case 4: for (i=0;i<4;i++) {newval[i] = autoD[i];} break;
                        case 5:
                            newval[0] = 0;
                            newval[1] = sys[1];
                            newval[2] = sys[2];
                        break;
                        case 6:
                            newval[0] = fz+1;
                            newval[1] = 0;
                            newval[2] = sys[3];
                            newval[3] = 0;
                            newval[4] = sys[4];
                        break;
                    }; 
            break;
          }
          byte = 10;
        break;
        case 3: //--------------------------------------------------- �������� ������� <����� ������> ------------------------------------------------------
          switch (byte){
            case 0: displ_num = 0; newSetButt = 1; break;
            case 1: if (--numMenu<0) numMenu = MAX_KOFF-1;    break;
            case 2: if (++numMenu>MAX_KOFF-1) numMenu = 0;    break;
            case 3: 
                    displ_num = numMenu+11; newSetButt = 1; 
                    switch (numMenu){
                        case 0:
                            newval[0] = analog[0].limCl;
                            newval[1] = analog[0].limT;
                            newval[2] = analog[0].limRh;
                            newval[3] = analog[0].limCO;
                            newval[4] = analog[0].minVal;
                            newval[5] = analog[0].maxVal;
                            newval[6] = analog[0].kP;
                            newval[7] = analog[0].kI;
                        break;
                        case 1:
                            newval[0] = analog[1].limCl;
                            newval[1] = analog[1].limT;
                            newval[2] = analog[1].limRh;
                            newval[3] = analog[1].limCO;
                            newval[4] = analog[1].minVal;
                            newval[5] = analog[1].maxVal;
                            newval[6] = analog[1].kP;
                            newval[7] = analog[1].kI;
                        break;
                        case 2:
                            newval[0] = analog[2].limCO;
                            newval[1] = analog[3].limCO;
                        break;
                        case 3:
                            newval[0] = analog[2].minVal;
                            newval[1] = analog[2].maxVal;
                            newval[2] = analog[2].kP;
                            newval[3] = analog[2].kI;
                            newval[4] = analog[2].limT;
                        break;
                        case 4:
                            newval[0] = analog[3].minVal;
                            newval[1] = analog[3].maxVal;
                            newval[2] = analog[3].kP;
                            newval[3] = analog[3].kI;
                            newval[4] = analog[3].limT;
                            newval[5] = analog[3].limCl;
                            newval[6] = analog[3].limRh;
                        break;
                        case 5:
                            newval[0] = digital[0].t1; 
                            newval[1] = digital[0].t2;
                            newval[2] = digital[0].k1;
                            newval[3] = digital[0].k2;
                            newval[4] = digital[1].t1;
                            newval[5] = digital[1].t2;
                            newval[6] = digital[1].k1;
                            newval[7] = digital[1].k2; 
                        break;
                        case 6:
                            newval[0] = digital[2].t1; 
                            newval[1] = digital[2].t2;
                            newval[2] = digital[2].k1;
                            newval[3] = digital[2].k2;
                            newval[4] = digital[3].t1;
                            newval[5] = digital[3].t2;
                            newval[6] = digital[3].k1;
                            newval[7] = digital[3].k2; 
                        break;
                    }; 
            break;
          }
          byte = 10;
        break;
        case 4: //--------------------------------------------------- ��������� ���� <������� ����> --------------------------------------------------------
          if(byte){
                setpoint.dry  = faza[fz].Dry  = newval[0];
                setpoint.soil = faza[fz].Soil = newval[1];
                setpoint.rh   = faza[fz].RH   = newval[2];
                setpoint.co2  = faza[fz].CO2  = newval[3];                 
          }
          displ_num = 2; newSetButt = 1;
          byte = 10;
        break;
        case 5: //--------------------------------------------------- ��������� ���� <�������� ����> -------------------------------------------------------
          if(byte){
                faza[fz].DeltaDry  = newval[0];
                faza[fz].DeltaSoil = newval[1];
                faza[fz].DeltaRH   = newval[2];
                faza[fz].DeltaCO2  = newval[3];                 
          }
          displ_num = 2; newSetButt = 1;
          byte = 10;
        break;
        case 6: //--------------------------------------------------- ��������� ���� <���������� ����> -------------------------------------------------------
          if(byte){
                faza[fz].EnableDry  = newval[0];
                faza[fz].EnableSoil = newval[1];
                faza[fz].EnableRH   = newval[2];
                faza[fz].EnableCO2  = newval[3];                 
          }
          displ_num = 2; newSetButt = 1;
          byte = 10;
        break;
        case 7: //--------------------------------------------------- ���������� � ----------------------------------------------------------------------------
          if(byte){  
            for (i=0;i<4;i++) {autoA[i] = newval[i];}
          }
          displ_num = 2; newSetButt = 1;
          byte = 10;
        break;
        case 8: //--------------------------------------------------- ���������� D ----------------------------------------------------------------------------
          if(byte){  
            for (i=0;i<4;i++) {autoD[i] = newval[i];}
          }
          displ_num = 2; newSetButt = 1;
          byte = 10;
        break;
        case 9: //--------------------------------------------------- ����������� ��������� 0 -------------------------------------------------------
          if(byte){
                timerDrying = newval[0];
                sys[1] = newval[1];
                sys[2] = newval[2];              
          }
          displ_num = 2; newSetButt = 1;
          byte = 10;
        break;
        case 10: //--------------------------------------------------- ����������� ��������� 1 -------------------------------------------------------
          if(byte){
                if ((sys[0] != newval[0]-1)&&(newval[0]>0&&newval[0]<5)){
                  sys[0] = newval[0]-1;
                  for (i=1; i<7; i++) clock_buffer[i] = 1; write_clock(clock_buffer);
                  ChangeFaza=1; setSP();
                }
                timerStop = newval[1];
                sys[3] = newval[2];
                switch (newval[3]){
                  case 3:
                      setpoint.dry = faza[sys[0]].Dry;
                      setpoint.soil = faza[sys[0]].Soil;
                      setpoint.rh = faza[sys[0]].RH;
                      setpoint.co2 = faza[sys[0]].CO2;
                  break;
                  case 13: copySP(); break;     // ��������� ���������� ���� ���������� � �������� ������������.
                  case 23: resetSP(); break;    // �������������� ���� ���������� � �������� � ���������, ������������� �� ������ ������������
                }; 
                sys[4] = newval[4];                    
          }
          displ_num = 2; newSetButt = 1;
          byte = 10;
        break;
        case 11: //--------------------------------------------------- ���������� ������� --------------------------------------------------------
          if(byte){
                analog[0].limCl = newval[0];
                analog[0].limT  = newval[1];
                analog[0].limRh = newval[2];
                analog[0].limCO = newval[3];
                analog[0].minVal = newval[4];
                analog[0].maxVal = newval[5];
                analog[0].kP = newval[6];
                analog[0].kI = newval[7];                 
          }
          displ_num = 3; newSetButt = 1;
          byte = 10;
        break;
        case 12: //--------------------------------------------------- �������� ������ ������� --------------------------------------------------------
          if(byte){
                analog[1].limCl = newval[0];
                analog[1].limT  = newval[1];
                analog[1].limRh = newval[2];
                analog[1].limCO = newval[3];
                analog[1].minVal = newval[4];
                analog[1].maxVal = newval[5];
                analog[1].kP = newval[6];
                analog[1].kI = newval[7];                 
          }
          displ_num = 3; newSetButt = 1;
          byte = 10;
        break; 
        case 13: //--------------------------------------------------- �������� ���������� --------------------------------------------------------
          if(byte){
                analog[2].limCO = newval[0];
                analog[3].limCO = newval[1];                
          }
          displ_num = 3; newSetButt = 1;
          byte = 10;
        break;
        case 14: //--------------------------------------------------- ���� ������� ���� --------------------------------------------------------
          if(byte){
                analog[2].minVal = newval[0];
                analog[2].maxVal = newval[1];
                analog[2].kP = newval[2];
                analog[2].kI = newval[3];
                analog[2].limT  = newval[4];                
          }
          displ_num = 3; newSetButt = 1;
          byte = 10;
        break;  
        case 15: //--------------------------------------------------- ���� �������� ���� --------------------------------------------------------
          if(byte){
                analog[3].minVal = newval[0];
                analog[3].maxVal = newval[1];
                analog[3].kP = newval[2];
                analog[3].kI = newval[3];
                analog[3].limT  = newval[4];
                analog[3].limCl = newval[5];
                analog[3].limRh = newval[6];                
          }
          displ_num = 3; newSetButt = 1;
          byte = 10;
        break;
        case 16: //--------------------------------------------------- ���� D12 ----------------------------------------------------------------------------
          if(byte){
                digital[0].t1 = newval[0];
                digital[0].t2 = newval[1];
                digital[0].k1 = newval[2];
                digital[0].k2 = newval[3];
                digital[1].t1 = newval[4];
                digital[1].t2 = newval[5];
                digital[1].k1 = newval[6];
                digital[1].k2 = newval[7];                 
          }
          displ_num = 3; newSetButt = 1;
          byte = 10;
        break;
        case 17: //--------------------------------------------------- ���� D34 ----------------------------------------------------------------------------
          if(byte){
                digital[2].t1 = newval[0];
                digital[2].t2 = newval[1];
                digital[2].k1 = newval[2];
                digital[2].k2 = newval[3];
                digital[3].t1 = newval[4];
                digital[3].t2 = newval[5];
                digital[3].k1 = newval[6];
                digital[3].k2 = newval[7];                 
          }
          displ_num = 3; newSetButt = 1;
          byte = 10;
        break;
        case 18: //--------------------------------------------------- �������� ������� <����� ������> ------------------------------------------------------
          switch (byte){
            case 0: displ_num = 0; newSetButt = 1; break;
            case 1: if (--numMenu<0) numMenu = 2;    break;
            case 2: if (++numMenu>2) numMenu = 0;    break;
            case 3: 
                   switch (numMenu){
                        case 0:
                            ptr_to_eeprom = &romcodeZ1[0][0];
                            if(devices!=SPOT1) byte=0;           // ���� �������� ������ ��� �������� ���������� ������
                            spot1 = devices;
                        break;
                        case 1:
                            ptr_to_eeprom = &romcodeZ2[0][0];
                            if(devices>SPOT2) byte=0;           // ���� �������� ������ ��� �������� ���������� ������
                            spot2 = devices;
                        break;
                        case 2:
                            ptr_to_eeprom = &romcodeZ3[0][0];
                            if(devices>SPOT3) byte=0;           // ���� �������� ������ ��� �������� ���������� ������
                            spot3 = devices;
                        break;
                   };
                   
                   if (byte){
                     ptr_to_ram = &rom_code[0][0];
                     for (i=0; i<devices; i++){     //i=0; i<end; i++
                        ptr_to_ram++;// ���������� 24h family code
                        for (byte=0; byte<7; byte++) *ptr_to_eeprom++ = *ptr_to_ram++;
                        ptr_to_ram++;// ���������� 0h
                     };
                     TFT_DrawString("��������",20,bottom_Y-40,2,0,BLACK,GREEN1);
                   }
                   else {
                     TFT_DrawString("������",20,bottom_Y-40,2,0,RED,YELLOW);
                   }; 
            break;
          }
          byte = 10;
        break;
     }
}

