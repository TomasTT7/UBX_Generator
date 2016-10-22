/*
    UBX-NAV-PVT (0x01 0x07)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define STEP        10              // seconds (max. 60)

uint32_t iTOW =     0;
uint16_t year =     2016;
uint8_t month =     10;
uint8_t day =       21;
uint8_t hour =      22;
uint8_t min =       13;
uint8_t sec =       0;
uint8_t valid =     0b00000100;
uint32_t tAcc =     1;
int32_t nano =      1;
uint8_t fixType =   3;
uint8_t flags =     0b00001100;
uint8_t flags2 =    0b11100000;
uint8_t numSV =     11;
int32_t lon =       0;
int32_t lat =       0;
int32_t height =    0;
int32_t hMSL =      0;
uint32_t hAcc =     1;
uint32_t vAcc =     1;
int32_t velN =      0;
int32_t velE =      0;
int32_t velD =      0;
int32_t gSpeed =    0;
int32_t headMot =   0;
uint32_t sAcc =     0;
uint32_t headAcc =  0;
uint16_t pDOP =     0;
int32_t headVeh =   0;

uint8_t ChecksumA = 0;
uint8_t ChecksumB = 0;

uint32_t count =    0;
char header1[] =    "uint8_t test0107_";
char header2[] =    "[100] = {";

uint8_t ubxmsg[] = {0xB5,0x62,0x01,0x07,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

int main()
{
    FILE * fpointerR;
    FILE * fpointerW;
    char singleLine[150];

    fpointerR = fopen("input.txt","r");
    fpointerW = fopen("output.txt","w");

    uint8_t inlat[13];
    uint8_t inlon[13];
    uint8_t inalt[10];

    while(!feof(fpointerR))
    {
        fgets(singleLine, 150, fpointerR);
        sscanf(singleLine, "%[^,],%[^,],%[^\n]\n", inlat, inlon, inalt);

        float inlatF = atof(inlat);
        float inlonF = atof(inlon);

        // PREPARE DATA
        count++;

        if(sec + STEP > 59)
        {
            if(min + 1 > 59)
            {
                if(hour + 1 > 23)
                {
                    day = (day + 1) % 30;
                    hour = (hour + 1) % 24;
                    min = (min + 1) % 60;
                    sec = (sec + STEP) % 60;
                }else{
                    hour++;
                    min = (min + 1) % 60;
                    sec = (sec + STEP) % 60;
                }
            }else{
                min++;
                sec = (sec + STEP) % 60;
            }
        }else{
            sec += STEP;
        }

        lat = (int32_t)(inlatF * 10000000.0);
        lon = (int32_t)(inlonF * 10000000.0);
        hMSL = atoi(inalt) * 1000;
        height = hMSL + 40000;

        // CONSTRUCT THE MESSAGE
        ubxmsg[6] = (iTOW >> 0);
        ubxmsg[7] = (iTOW >> 8);
        ubxmsg[8] = (iTOW >> 16);
        ubxmsg[9] = (iTOW >> 24);
        ubxmsg[10] = (year >> 0);
        ubxmsg[11] = (year >> 8);
        ubxmsg[12] = (month >> 0);
        ubxmsg[13] = (day >> 0);
        ubxmsg[14] = (hour >> 0);
        ubxmsg[15] = (min >> 0);
        ubxmsg[16] = (sec >> 0);
        ubxmsg[17] = (valid >> 0);
        ubxmsg[18] = (tAcc >> 0);
        ubxmsg[19] = (tAcc >> 8);
        ubxmsg[20] = (tAcc >> 16);
        ubxmsg[21] = (tAcc >> 24);
        ubxmsg[22] = (nano >> 0);
        ubxmsg[23] = (nano >> 8);
        ubxmsg[24] = (nano >> 16);
        ubxmsg[25] = (nano >> 24);
        ubxmsg[26] = (fixType >> 0);
        ubxmsg[27] = (flags >> 0);
        ubxmsg[28] = (flags2 >> 0);
        ubxmsg[29] = (numSV >> 0);
        ubxmsg[30] = (lon >> 0);
        ubxmsg[31] = (lon >> 8);
        ubxmsg[32] = (lon >> 16);
        ubxmsg[33] = (lon >> 24);
        ubxmsg[34] = (lat >> 0);
        ubxmsg[35] = (lat >> 8);
        ubxmsg[36] = (lat >> 16);
        ubxmsg[37] = (lat >> 24);
        ubxmsg[38] = (height >> 0);
        ubxmsg[39] = (height >> 8);
        ubxmsg[40] = (height >> 16);
        ubxmsg[41] = (height >> 24);
        ubxmsg[42] = (hMSL >> 0);
        ubxmsg[43] = (hMSL >> 8);
        ubxmsg[44] = (hMSL >> 16);
        ubxmsg[45] = (hMSL >> 24);
        ubxmsg[46] = (hAcc >> 0);
        ubxmsg[47] = (hAcc >> 8);
        ubxmsg[48] = (hAcc >> 16);
        ubxmsg[49] = (hAcc >> 24);
        ubxmsg[50] = (vAcc >> 0);
        ubxmsg[51] = (vAcc >> 8);
        ubxmsg[52] = (vAcc >> 16);
        ubxmsg[53] = (vAcc >> 24);
        ubxmsg[54] = (velN >> 0);
        ubxmsg[55] = (velN >> 8);
        ubxmsg[56] = (velN >> 16);
        ubxmsg[57] = (velN >> 24);
        ubxmsg[58] = (velE >> 0);
        ubxmsg[59] = (velE >> 8);
        ubxmsg[60] = (velE >> 16);
        ubxmsg[61] = (velE >> 24);
        ubxmsg[62] = (velD >> 0);
        ubxmsg[63] = (velD >> 8);
        ubxmsg[64] = (velD >> 16);
        ubxmsg[65] = (velD >> 24);
        ubxmsg[66] = (gSpeed >> 0);
        ubxmsg[67] = (gSpeed >> 8);
        ubxmsg[68] = (gSpeed >> 16);
        ubxmsg[69] = (gSpeed >> 24);
        ubxmsg[70] = (headMot >> 0);
        ubxmsg[71] = (headMot >> 8);
        ubxmsg[72] = (headMot >> 16);
        ubxmsg[73] = (headMot >> 24);
        ubxmsg[74] = (sAcc >> 0);
        ubxmsg[75] = (sAcc >> 8);
        ubxmsg[76] = (sAcc >> 16);
        ubxmsg[77] = (sAcc >> 24);
        ubxmsg[78] = (headAcc >> 0);
        ubxmsg[79] = (headAcc >> 8);
        ubxmsg[80] = (headAcc >> 16);
        ubxmsg[81] = (headAcc >> 24);
        ubxmsg[82] = (pDOP >> 0);
        ubxmsg[83] = (pDOP >> 8);
        ubxmsg[90] = (headVeh >> 0);
        ubxmsg[91] = (headVeh >> 8);
        ubxmsg[92] = (headVeh >> 16);
        ubxmsg[93] = (headVeh >> 24);

        // PRINT THE RESULT
        printf("%s%d%s", header1, count, header2);
        printf("0xB5,0x62,0x01,0x07,0x92,0x00,");
        printf("0x%02X,0x%02X,0x%02X,0x%02X,",
                (uint8_t)(iTOW >> 0), (uint8_t)(iTOW >> 8), (uint8_t)(iTOW >> 16), (uint8_t)(iTOW >> 24));
        printf("0x%02X,0x%02X,", (uint8_t)(year >> 0), (uint8_t)(year >> 8));
        printf("0x%02X,", (month >> 0));
        printf("0x%02X,", (day >> 0));
        printf("0x%02X,", (hour >> 0));
        printf("0x%02X,", (min >> 0));
        printf("0x%02X,", (sec >> 0));
        printf("0x%02X,", (valid >> 0));
        printf("0x%02X,0x%02X,0x%02X,0x%02X,",
                (uint8_t)(tAcc >> 0), (uint8_t)(tAcc >> 8), (uint8_t)(tAcc >> 16), (uint8_t)(tAcc >> 24));
        printf("0x%02" PRIX8 ",", (uint8_t)(nano >> 0));
        printf("0x%02" PRIX8 ",", (uint8_t)(nano >> 8));
        printf("0x%02" PRIX8 ",", (uint8_t)(nano >> 16));
        printf("0x%02" PRIX8 ",", (uint8_t)(nano >> 24));
        printf("0x%02X,", (fixType >> 0));
        printf("0x%02X,", (flags >> 0));
        printf("0x%02X,", (flags2 >> 0));
        printf("0x%02X,", (numSV >> 0));
        printf("0x%02" PRIX8 ",", (uint8_t)(lon >> 0));
        printf("0x%02" PRIX8 ",", (uint8_t)(lon >> 8));
        printf("0x%02" PRIX8 ",", (uint8_t)(lon >> 16));
        printf("0x%02" PRIX8 ",", (uint8_t)(lon >> 24));
        printf("0x%02" PRIX8 ",", (uint8_t)(lat >> 0));
        printf("0x%02" PRIX8 ",", (uint8_t)(lat >> 8));
        printf("0x%02" PRIX8 ",", (uint8_t)(lat >> 16));
        printf("0x%02" PRIX8 ",", (uint8_t)(lat >> 24));
        printf("0x%02" PRIX8 ",", (uint8_t)(height >> 0));
        printf("0x%02" PRIX8 ",", (uint8_t)(height >> 8));
        printf("0x%02" PRIX8 ",", (uint8_t)(height >> 16));
        printf("0x%02" PRIX8 ",", (uint8_t)(height >> 24));
        printf("0x%02" PRIX8 ",", (uint8_t)(hMSL >> 0));
        printf("0x%02" PRIX8 ",", (uint8_t)(hMSL >> 8));
        printf("0x%02" PRIX8 ",", (uint8_t)(hMSL >> 16));
        printf("0x%02" PRIX8 ",", (uint8_t)(hMSL >> 24));
        printf("0x%02X,0x%02X,0x%02X,0x%02X,",
                (uint8_t)(hAcc >> 0), (uint8_t)(hAcc >> 8), (uint8_t)(hAcc >> 16), (uint8_t)(hAcc >> 24));
        printf("0x%02X,0x%02X,0x%02X,0x%02X,",
                (uint8_t)(vAcc >> 0), (uint8_t)(vAcc >> 8), (uint8_t)(vAcc >> 16), (uint8_t)(vAcc >> 24));
        printf("0x%02" PRIX8 ",", (uint8_t)(velN >> 0));
        printf("0x%02" PRIX8 ",", (uint8_t)(velN >> 8));
        printf("0x%02" PRIX8 ",", (uint8_t)(velN >> 16));
        printf("0x%02" PRIX8 ",", (uint8_t)(velN >> 24));
        printf("0x%02" PRIX8 ",", (uint8_t)(velE >> 0));
        printf("0x%02" PRIX8 ",", (uint8_t)(velE >> 8));
        printf("0x%02" PRIX8 ",", (uint8_t)(velE >> 16));
        printf("0x%02" PRIX8 ",", (uint8_t)(velE >> 24));
        printf("0x%02" PRIX8 ",", (uint8_t)(velD >> 0));
        printf("0x%02" PRIX8 ",", (uint8_t)(velD >> 8));
        printf("0x%02" PRIX8 ",", (uint8_t)(velD >> 16));
        printf("0x%02" PRIX8 ",", (uint8_t)(velD >> 24));
        printf("0x%02" PRIX8 ",", (uint8_t)(gSpeed >> 0));
        printf("0x%02" PRIX8 ",", (uint8_t)(gSpeed >> 8));
        printf("0x%02" PRIX8 ",", (uint8_t)(gSpeed >> 16));
        printf("0x%02" PRIX8 ",", (uint8_t)(gSpeed >> 24));
        printf("0x%02" PRIX8 ",", (uint8_t)(headMot >> 0));
        printf("0x%02" PRIX8 ",", (uint8_t)(headMot >> 8));
        printf("0x%02" PRIX8 ",", (uint8_t)(headMot >> 16));
        printf("0x%02" PRIX8 ",", (uint8_t)(headMot >> 24));
        printf("0x%02X,0x%02X,0x%02X,0x%02X,",
                (uint8_t)(sAcc >> 0), (uint8_t)(sAcc >> 8), (uint8_t)(sAcc >> 16), (uint8_t)(sAcc >> 24));
        printf("0x%02X,0x%02X,0x%02X,0x%02X,",
                (uint8_t)(headAcc >> 0), (uint8_t)(headAcc >> 8), (uint8_t)(headAcc >> 16), (uint8_t)(headAcc >> 24));
        printf("0x%02X,0x%02X,", (uint8_t)(pDOP >> 0), (uint8_t)(pDOP >> 8));
        printf("0x00,0x00,0x00,0x00,0x00,0x00,");
        printf("0x%02" PRIX8 ",", (uint8_t)(headVeh >> 0));
        printf("0x%02" PRIX8 ",", (uint8_t)(headVeh >> 8));
        printf("0x%02" PRIX8 ",", (uint8_t)(headVeh >> 16));
        printf("0x%02" PRIX8 ",", (uint8_t)(headVeh >> 24));
        printf("0x00,0x00,0x00,0x00,");

        // CHECKSUM calculation
        ChecksumA = 0;
        ChecksumB = 0;

        uint8_t y;

        for(y = 2; y < 98; y++)
        {
            ChecksumA = ChecksumA + ubxmsg[y];
            ChecksumB = ChecksumA + ChecksumB;
        }

        printf("0x%02X,0x%02X", ChecksumA, ChecksumB);
        printf("};\n");

        ubxmsg[98] = (ChecksumA >> 0);
        ubxmsg[99] = (ChecksumB >> 0);

        // SAVE TO A FILE
        fprintf(fpointerW, "%s%d%s", header1, count, header2);

        uint8_t i;

        for(i = 0; i < 100; i++)
        {
            fprintf(fpointerW, "0x%02X", ubxmsg[i]);
            if(i < 99)fprintf(fpointerW, ",");
        }

        fprintf(fpointerW, "};\n");
    }

    fclose(fpointerR);
    fclose(fpointerW);

    return 0;
}
