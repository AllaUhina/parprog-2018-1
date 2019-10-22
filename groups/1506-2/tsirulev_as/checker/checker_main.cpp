#include <cstdio> 
#include <cmath> 
#include <string>

using namespace std;

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result 
{ 
	private: 
		FILE * bur;
	public:
		enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
		result (bool read = false) 
		{ 
			if (read) 
				bur = fopen("result.txt", "r");
			else 
				bur = fopen("result.txt", "w"); 
		}

		~result() 
		{
			fclose (bur); 
		} 
		void write_type(ext_cls t) //записать что-то
		{ 
			fwrite(&t, sizeof (t), 1, bur); 
		}
		void write_verdict(verdict v) //записать вердикт
		{ 
			write_type(ext_cls::VERDICT);
			fwrite(&v, sizeof (v), 1, bur); 
		}
		void write_message(string str) 
		{
			write_type(ext_cls::MESSAGE);
			int l = str.size ();
			fwrite(&l, sizeof (l), 1, bur);
			fwrite (&str[0], sizeof (str[0]), l, bur);
		}
	
}checker_result;
////////////////////////////////////////////////////////////////////////////////////////////

int main (int argc, char * argv[]) 
{ 
	char *user_answer;
	char *mkl_answer;
	if(argc>1)
	{
		user_answer=argv[1];
		mkl_answer=argv[2];
	}
	FILE * user_file = fopen(user_answer, "rb");//ответ алгоритма
	FILE * mkl_file = fopen(mkl_answer, "rb");//ответ mkl
	int noNul_cnt,m_size; 

	// Выделяем память для матрицы ответа жюри и ответа участника 
	fread(&noNul_cnt,sizeof(noNul_cnt),1,user_file);
	fread(&m_size,sizeof(m_size),1,user_file);

	double *user_vals=new double[noNul_cnt];
	int *user_rows=new int[noNul_cnt];
	int *user_index=new int[m_size+1];

	double *mkl_vals=new double[noNul_cnt];
	int *mkl_rows=new int[noNul_cnt];
	int *mkl_index=new int[m_size+1];

	fread(user_vals,sizeof(user_vals),1,user_file);
	fread(user_rows,sizeof(user_rows),1,user_file);
	fread(user_index,sizeof(user_index),1,user_file);

	fread(mkl_vals,sizeof(mkl_vals),1,mkl_file);
	fread(mkl_rows,sizeof(mkl_rows),1,mkl_file);
	fread(mkl_index,sizeof(mkl_index),1,mkl_file);

	// вычисление расхождения и установление несоответствия в индексах
	double diff_val = 0.0;
	bool rows_eqal=true;
	bool inds_eqal=true;
	for (int i = 0; i <noNul_cnt; i++) 
		diff_val += (user_vals[i] - mkl_vals[i]) * (user_vals[i] - mkl_vals[i]);

	for (int i = 0; i <noNul_cnt; i++) 
		if(user_rows[i]!=mkl_rows[i])
			rows_eqal=false;

	for (int i = 0; i <m_size+1; i++) 
		if(user_index[i]!=mkl_index[i])
			inds_eqal=false;

	if ((diff_val < 1e-4) &&(rows_eqal)&&(inds_eqal))
	{ 
		checker_result.write_message ("AC. All are equal.");
		checker_result.write_verdict (verdict::AC); 
	} 
	else 
	{
		if(!rows_eqal)
			checker_result.write_message ("WA. Wrong row");
		if(!inds_eqal)
			checker_result.write_message ("WA. Wrong index");
		if(diff_val>=1e-4)
			checker_result.write_message ("WA. Wrong values");
		checker_result.write_verdict (verdict::WA);
	}
	// версии OpenMP на данный момент нет. Поэтому запись времени будет написана позже
	
	fclose(mkl_file); 
	fclose(user_file);
	return 0; 
}