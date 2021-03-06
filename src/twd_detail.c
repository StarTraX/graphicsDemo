
#include "twd_detail.h"
#include <main.h>
static Window *window;
static GBitmap *backgroundBitmap;

int actualImageWidth =  (int)(144 * 3.14159);
float actualImageWidthRatio = (144 * 3.14159)/360;

//static void canvas_update_proc(Layer *this_layer, GContext *ctx) {
//	}

bool isPxSetAt(int x, int y ){
	// pixel at row y, col x is in myAddr[y*18+ (int)x/8]
	int charPos = (int)(x/8+18*y);
	int myChar = twdBackgroundImageBitArray[charPos];
	int bitPos = x % 8;
	int isSet = (1 << bitPos) & myChar; // 1 if set
	//printf("Px at row %d, col %d, charPos %d, bitPos %d, char %x is %d ", y, x,charPos, bitPos, myChar, isSet );
	if (isSet >0 ) return false;
	else return true;
}
static const uint16_t __ACOS[]={ // 100* angles (radians) whose cosine are -1 to +1 in /500ths 
	3142,3078,3052,3032,3015,3000,2987,2974,2962,2952,2941,2931,2922,2913,2904,2896,2888,2880,2872,2865,2858,2851,2844,2837,2831,2824,2818,2811,2805,2799,2793,2788,2782,2776,2771,2765,2760,2754,2749,2744,2739,
2734,2729,2724,2719,2714,2709,2705,2700,2695,2691,2686,2681,2677,2673,2668,2664,2659,2655,2651,2647,2642,2638,2634,2630,2626,2622,2618,2614,2610,2606,2602,2598,2594,2591,2587,2583,2579,2575,2572,2568,2564,
2561,2557,2553,2550,2546,2543,2539,2536,2532,2529,2525,2522,2518,2515,2512,2508,2505,2501,2498,2495,2491,2488,2485,2482,2478,2475,2472,2469,2465,2462,2459,2456,2453,2450,2447,2443,2440,2437,2434,2431,2428,
2425,2422,2419,2416,2413,2410,2407,2404,2401,2398,2395,2392,2389,2386,2383,2380,2377,2375,2372,2369,2366,2363,2360,2357,2355,2352,2349,2346,2343,2341,2338,2335,2332,2330,2327,2324,2321,2319,2316,2313,2310,
2308,2305,2302,2300,2297,2294,2292,2289,2286,2284,2281,2278,2276,2273,2271,2268,2265,2263,2260,2258,2255,2252,2250,2247,2245,2242,2240,2237,2234,2232,2229,2227,2224,2222,2219,2217,2214,2212,2209,2207,2204,
2202,2199,2197,2194,2192,2190,2187,2185,2182,2180,2177,2175,2172,2170,2168,2165,2163,2160,2158,2156,2153,2151,2148,2146,2144,2141,2139,2136,2134,2132,2129,2127,2125,2122,2120,2118,2115,2113,2111,2108,2106,
2104,2101,2099,2097,2094,2092,2090,2087,2085,2083,2081,2078,2076,2074,2071,2069,2067,2065,2062,2060,2058,2056,2053,2051,2049,2047,2044,2042,2040,2038,2035,2033,2031,2029,2026,2024,2022,2020,2018,2015,2013,
2011,2009,2006,2004,2002,2000,1998,1995,1993,1991,1989,1987,1984,1982,1980,1978,1976,1974,1971,1969,1967,1965,1963,1961,1958,1956,1954,1952,1950,1948,1946,1943,1941,1939,1937,1935,1933,1931,1928,1926,1924,
1922,1920,1918,1916,1913,1911,1909,1907,1905,1903,1901,1899,1897,1894,1892,1890,1888,1886,1884,1882,1880,1878,1875,1873,1871,1869,1867,1865,1863,1861,1859,1857,1855,1853,1850,1848,1846,1844,1842,1840,1838,
1836,1834,1832,1830,1828,1826,1823,1821,1819,1817,1815,1813,1811,1809,1807,1805,1803,1801,1799,1797,1795,1793,1791,1789,1786,1784,1782,1780,1778,1776,1774,1772,1770,1768,1766,1764,1762,1760,1758,1756,1754,
1752,1750,1748,1746,1744,1742,1740,1738,1736,1734,1731,1729,1727,1725,1723,1721,1719,1717,1715,1713,1711,1709,1707,1705,1703,1701,1699,1697,1695,1693,1691,1689,1687,1685,1683,1681,1679,1677,1675,1673,1671,
1669,1667,1665,1663,1661,1659,1657,1655,1653,1651,1649,1647,1645,1643,1641,1639,1637,1635,1633,1631,1629,1627,1625,1623,1621,1619,1617,1615,1613,1611,1609,1607,1605,1603,1601,1599,1597,1595,1593,1591,1589,
1587,1585,1583,1581,1579,1577,1575,1573,1571,1569,1567,1565,1563,1561,1559,1557,1555,1553,1551,1549,1547,1545,1543,1541,1539,1537,1535,1533,1531,1529,1527,1525,1523,1521,1519,1517,1515,1513,1511,1509,1507,
1505,1503,1501,1499,1497,1495,1493,1491,1489,1487,1485,1483,1481,1479,1477,1475,1473,1471,1469,1467,1465,1463,1461,1459,1457,1455,1453,1451,1448,1446,1444,1442,1440,1438,1436,1434,1432,1430,1428,1426,1424,
1422,1420,1418,1416,1414,1412,1410,1408,1406,1404,1402,1400,1398,1396,1394,1392,1390,1388,1386,1384,1382,1380,1378,1376,1374,1371,1369,1367,1365,1363,1361,1359,1357,1355,1353,1351,1349,1347,1345,1343,1341,
1339,1337,1335,1333,1330,1328,1326,1324,1322,1320,1318,1316,1314,1312,1310,1308,1306,1304,1302,1299,1297,1295,1293,1291,1289,1287,1285,1283,1281,1279,1277,1274,1272,1270,1268,1266,1264,1262,1260,1258,1256,
1253,1251,1249,1247,1245,1243,1241,1239,1237,1234,1232,1230,1228,1226,1224,1222,1220,1217,1215,1213,1211,1209,1207,1205,1203,1200,1198,1196,1194,1192,1190,1187,1185,1183,1181,1179,1177,1175,1172,1170,1168,
1166,1164,1161,1159,1157,1155,1153,1151,1148,1146,1144,1142,1140,1137,1135,1133,1131,1129,1126,1124,1122,1120,1117,1115,1113,1111,1109,1106,1104,1102,1100,1097,1095,1093,1091,1088,1086,1084,1082,1079,1077,
1075,1072,1070,1068,1066,1063,1061,1059,1056,1054,1052,1050,1047,1045,1043,1040,1038,1036,1033,1031,1029,1026,1024,1022,1019,1017,1015,1012,1010,1007,1005,1003,1000,998,996,993,991,988,986,984,981,
979,976,974,972,969,967,964,962,959,957,955,952,950,947,945,942,940,937,935,932,930,927,925,922,920,917,915,912,910,907,905,902,900,897,894,892,889,887,884,881,879,
876,874,871,868,866,863,861,858,855,853,850,847,845,842,839,837,834,831,828,826,823,820,818,815,812,809,807,804,801,798,795,793,790,787,784,781,778,776,773,770,767,
764,761,758,755,752,750,747,744,741,738,735,732,729,726,723,720,717,714,711,707,704,701,698,695,692,689,686,682,679,676,673,670,666,663,660,657,653,650,647,644,640,
637,633,630,627,623,620,616,613,609,606,602,599,595,592,588,584,581,577,574,570,566,562,559,555,551,547,543,539,536,532,528,524,520,516,512,507,503,499,495,491,486,
482,478,473,469,465,460,456,451,446,442,437,432,428,423,418,413,408,403,398,392,387,382,376,371,365,360,354,348,342,336,330,324,318,311,304,298,291,284,277,269,262,
254,246,237,229,220,210,200,190,179,168,155,142,127,110,89,63,0};

static const char twdBackgroundVerticalgGidlinePos[] = // built from pws/dashboard/wind/index.php
		{1,16,0,2,32,0,4,64,0,8,128,0,16,0,2,32,0,4,64,0,8,128,0,16,0,2,32,0,4,64,0,8,128,
		 0,16,0,2,32,0,4,64,0,8,128,0,16,0,1,32,0,4,64,0,8,128,0,0};


static void canvas_update_proc(Layer *this_layer, GContext *ctx) {
	//printf("in canvas_update_proc histDataSize: %d", *histDataSize);
	printf ("canvas_update_proc " );
	/*
	int colIdx; //column
	int rowIdx; //row
	int rowMax = 20;
	int colMax = 144;
	for (rowIdx=0; rowIdx < rowMax; rowIdx++){ //row
		for (colIdx=0; colIdx < colMax; colIdx++){ //column
		float cosRatio = 1 - (float) colIdx/72;
			//printf("Here rowIdx %d colIdx %d ", rowIdx, colIdx );
			cosRatio *= 500;
			cosRatio += 500; 				
			float theta = __ACOS[(int)(cosRatio)] ;
			theta /= 1000;
			float sourceX = 72*theta ; // rTheta			
			sourceX += *start * actualImageWidthRatio ; //
			sourceX -= actualImageWidth*(sourceX > actualImageWidth?1:0); // fold it back 				
			int bitAddress = rowIdx * actualImageWidth // 452 bits Px per row 
				 + sourceX; 
			int arrayIdx = (int) bitAddress/8; // it's an 8  byte
			int bitIdx =  bitAddress % 8;
			//printf( "arrayIdx %d" ,arrayIdx );
			//printf("twdBackgroundImageBitArray[arrayIdx] %d", twdBackgroundImageBitArray[arrayIdx]);
			int pxValue = (1 << bitIdx) & twdBackgroundImageBitArray[arrayIdx] ;
			if (pxValue >0 ) graphics_draw_pixel(ctx, GPoint(colIdx,rowIdx));
		}
		//break;
	}
	
	printf("Done heading");
	// --- draw the verticle gridlines 
	for (colIdx=0; colIdx < colMax; colIdx++){ //column
		float cosRatio = 1 - (float) colIdx/72;
		cosRatio *= 500;
		cosRatio += 500; 				
		float theta = __ACOS[(int)(cosRatio)] ;
		theta /= 1000;
		float sourceX = 72*theta ; // rTheta			
		sourceX += *start * actualImageWidthRatio ; //
		sourceX -= actualImageWidth*(sourceX > actualImageWidth?1:0); // fold it back 				
		int bitAddress =  sourceX; // rowIdx of ZERO
		int arrayIdx = (int) bitAddress/8; // it's an 8  byte
		int bitIdx =  bitAddress % 8;
		int pxValue = (1 << bitIdx) & twdBackgroundVerticalgGidlinePos[arrayIdx] ;
		if (pxValue >0 ) {
			graphics_draw_line(ctx, GPoint(colIdx, 20) ,GPoint(colIdx, 144));
			//printf("Found one at %d ", colIdx);
		}			
	}


	
	//------build the cumulative array ---------
	//goto SKIP1;
	//SKIP1:;
	//int mLength = sizeof(*twdWindDirImageRecentBitArray) / sizeof(twdWindDirImageRecentBitArray[0]) ;
	//printf("sizeof(twdWindDirImageRecentBitArray: %d", sizeof(*twdWindDirImageRecentBitArray ));
	//printf("sizeof(twdWindDirImageRecentBitArray[0]: %d",sizeof(twdWindDirImageRecentBitArray[0] ));
	//printf("mLength: %d",mLength );
*/

	//START OF PROBLEM CODE 
	int mSize =*histDataSize; 
	APP_LOG(APP_LOG_LEVEL_INFO, "mSize %d ", mSize);
	int mSumArray[442];
	APP_LOG(APP_LOG_LEVEL_INFO,"mSumArray ");
	int runningTotal=0;	
	APP_LOG(APP_LOG_LEVEL_INFO,"runningTotal %d ", runningTotal);
	for (int i=0; i<mSize; i++){
		//runningTotal = runningTotal + twdWindDirImageRecentBitArray[i];
		//runningTotal = runningTotal +5;
		//mSumArray[i] = runningTotal; 
	} 

	printf ("runningTotal %d mSumArray[4] %d ", runningTotal, mSumArray[4]);
	//END  OF PROBLEM CODE 
	
	/*
	printf("sumArray[440]  %d ", sumArray[440]);

	printf("Last address: %d",runningTotal );
	// ------ draw the RecentHistory data  from cumulative 
	int prevAddress = 0;
	for (rowIdx=0; rowIdx < rowMax; rowIdx++){ //row
		
		for (colIdx=0; colIdx < colMax; colIdx++){ //column
			float cosRatio = 1 - (float) colIdx/72;
			cosRatio *= 500;
			cosRatio += 500; 				
			float theta = __ACOS[(int)(cosRatio)] ;
			theta /= 1000;
			float sourceX = 72*theta ; // rTheta			
			sourceX += *start * actualImageWidthRatio ; //
			sourceX -= actualImageWidth*(sourceX > actualImageWidth?1:0); // fold it back 				
			int bitAddress = rowIdx * actualImageWidth // 452 bits Px per row 
				 + sourceX; 

			//int arrayIdx = (int) bitAddress/8; // it's an 8  byte
			//int bitIdx =  bitAddress % 8;
			//int pxValue = (1 << bitIdx) & twdWindDirImageRecentBitArray[arrayIdx] ;

			// Look up from cumulative array -----/
			int j ;
			if (bitAddress > prevAddress)
				j = prevAddress;
			else j = 0;
			prevAddress = j;
			for (int i =0; i < *histDataSize; i++){
				if (bitAddress >= sumArray [i]){//found the byte
					if ( (i & 1) ==1)// test if the value is even
						graphics_draw_pixel(ctx, GPoint((colIdx),rowIdx+20));
				}
			} 
			//if (pxValue >0 ) graphics_draw_pixel(ctx, GPoint((colIdx+20),rowIdx));
		}
		//break;
	}

// SKIP1: ;
*/
}

static void window_load(Window *window) {
  // Create Layer for the canvas
	
	printf("twd_detail in window_load");
	*start = 0;
	s_canvas_layer = layer_create(GRect(0, 12, 144,144));
	layer_add_child(window_get_root_layer(window), s_canvas_layer);
	printf("twd_detail window_load layer_add_child ");
	layer_set_update_proc(s_canvas_layer, canvas_update_proc);
	printf("twd_detail window_load layer_set_update_proc heap_bytes_free: %d   ",(int) heap_bytes_free() );

}

static void window_unload(Window *window) {
  	window_stack_remove(window, true);
  	window_destroy(window);	
	gbitmap_destroy(backgroundBitmap);
	window_stack_pop(false);
}
void twd_detail(void) {
	printf("In twd_detail");
	//send_to_phone(TupletCString(100, "twd_detail"));
	 window = window_create();
	 window_set_window_handlers(window, (WindowHandlers) {
		.load = window_load,
		.unload = window_unload,

	  });
	  window_stack_push(window, true);
	}




