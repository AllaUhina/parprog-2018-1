// solver.cpp : Defines the entry point for the console application.
//

#include <cstdio> 
#include <omp.h> 
#include <iostream>
#include <string>
#include <exception>
#include <algorithm>


void MyQSort(long double * arr, unsigned long long size);
void StandardSort(long double* arr, unsigned long long size);

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		std::cerr << "too little args";
		return argc;
	}

	//argv[1] - èìÿ òåñòà
	//argv[2] - êîëè÷åñòâî ïîòîêîâ(íåîáÿçàòåëüíûé àðãóìåíò)

	std::string test_name = argv[1];//èìÿ òåñòà

	int num_threads = 1;
	if (argc > 2)
		num_threads = atoi(argv[2]);


	auto filein = freopen(argv[1], "rb", stdin);					//âõîäíûå äàííûå
	if (!filein)
	{
		std::cerr << "input file not found" << std::endl;
		return 1;
	}


	auto name = test_name + ".ans";
	FILE * out = fopen(name.c_str(), "wb");		//âûõîäíûå äàííûå("îòâåò ó÷àñòíèêà") - ðåçóëüòàò ðàáîòû íàïèñàííîé ôóíêöèè ñîðòèðîâêè
	auto name1 = test_name + ".txt";
	FILE * answer = fopen(name1.c_str(), "wb");	//ïðàâèëüíûé îòâåò("îòâåò æþðè") - ðåçóëüòàò ðàáîòû ýòàëîííîé ôóíêöèè ñîðòèðîâêè

	unsigned long long N = 0;//ðàçìåð ìàññèâà
	fread(&N, sizeof(N), 1, stdin);//ñ÷èòûâàåì ðàçìåð ìàññèâà
	long double * arr = new long double[N];
	fread(arr, sizeof(*arr), N, stdin);//ñ÷èòûâàåì ìàññèâ
	fclose(stdin);
	long double * arr1 = new long double[N];//ìàññèâ äëÿ ýòàëîííîé ôóíêöèè
	memcpy(arr1, arr, sizeof(*arr) * N);


	omp_set_num_threads(num_threads);//êîëè÷åñòâî ïîòîêîâ
									 //ðåøåíèå çàäà÷è ñîðòèðîâêè - ðåçóëüòàò çàïèñûâàåòñÿ â "âûõîäíûå äàííûå"
	try
	{
		double time = omp_get_wtime();
		MyQSort(arr, N);
		time = omp_get_wtime() - time;

		fwrite(&time, sizeof(time), 1, out);//çàïèñûâàåì âðåìÿ ðàáîòû ñîðòèðîâêè
		fwrite(arr, sizeof(*arr), N, out);//çàïèñûâàåì ðåçóëüòàò ðàáîòû ñîðòèðîâêè

		std::cerr << "time = " << time << " is sorted? - " << std::boolalpha << std::is_sorted(arr, arr + sizeof(arr) / sizeof(*arr)) << std::endl;
	}
	catch (std::exception e)
	{
		fwrite(e.what(), 1, strlen(e.what()), out);
	}
	fclose(out);

	omp_set_num_threads(1);
	//ðåøåíèå çàäà÷è ñîðòèðîâêè - ðåçóëüòàò çàïèñûâàåòñÿ â "ïðàâèëüíûé îòâåò.txt"
	try
	{
		double time = omp_get_wtime();
		StandardSort(arr1, N);
		time = omp_get_wtime() - time;

		fwrite(&time, sizeof(time), 1, answer);//çàïèñûâàåì âðåìÿ ðàáîòû ñîðòèðîâêè
		fwrite(arr1, sizeof(*arr1), N, answer);//çàïèñûâàåì ðåçóëüòàò ðàáîòû ñîðòèðîâêè

		std::cerr << "time = " << time << " is sorted? - " << std::boolalpha << std::is_sorted(arr1, arr1 + sizeof(arr1) / sizeof(*arr1)) << std::endl;
	}
	catch (std::exception e)
	{
		fwrite(e.what(), 1, strlen(e.what()), answer);
	}
	fclose(answer);


	return 0;
}
