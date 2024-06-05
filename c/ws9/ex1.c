/*************************************************************************
Poject: struct part 2
Author: karam aamar
Reviewer: evgani
Date: 26/07/22
Version: 1.0
*************************************************************************/

#include <stdio.h>  /* print */
#include <string.h> /* memcpy */
#include <stdlib.h> /* allocation */
#include <assert.h> /* NULL pointers check */
#include <errno.h>  /* errors types */

#include "ex1.h"

void SaveStudent(FILE* outfile ,student_ty* student);
void LoadStudent(FILE* file,student_ty* studentload2);

static void InitStruct(student_ty* student);
static void ImplementFunc(student_ty* student , student_ty* student2);
static void TestFunc(student_ty* student,student_ty* student2);

static void SaveStudentImpl(FILE* outfile , student_ty* student);
static void SaveStudentName(FILE* outfile , char* str_name);
static void SaveStudentGrades(FILE* outfile , student_grades_ty* studentgrade);
static void SaveHumanisiticGrades(FILE* outfile 
					, humansitc_grades_ty* humangrade);
static void SaveVerbalGrades(FILE* outfile , verbal_grades_ty* verbalgrade);
static void SaveMindGrades(FILE* outfile, mind_grades_ty* mindgrades);
static void SaveRealGrades(FILE* outfile, real_grades_ty* realgrades);
static void SaveNatureGrades(FILE* outfile, nature_grades_ty* naturegrades);
static void SaveEngGrades(FILE* outfile, engineering_grades_ty* enggrades);

static void LoadStudentImpl(FILE* outfile,student_ty* student);
static void LoadStudentName(FILE* outfile,char* str_name);
static void LoadStudentGrades(FILE* outfile,student_grades_ty* studentgrade);
static void LoadHumanisiticGrades(FILE* outfile,humansitc_grades_ty* humangrade);
static void LoadVerbalGrades(FILE* outfile , verbal_grades_ty* verbalgrade);
static void LoadMindGrades(FILE* outfile, mind_grades_ty* mindgrades);
static void LoadRealGrades(FILE* outfile, real_grades_ty* realgrades);
static void LoadNatureGrades(FILE* outfile, nature_grades_ty* naturegrades);
static void LoadEngGrades(FILE* outfile, engineering_grades_ty* enggrades);

int main()
{
	student_ty student;
	student_ty student2;
	
	InitStruct(&student);
	ImplementFunc(&student, &student2);
	
		
	return 0;
}

static void InitStruct(student_ty* student)
{
	assert(NULL != student);
	memcpy(student-> first_name, "karam\0", strlen("karam")+1);
	memcpy(student-> last_name,  "aamar\0", strlen("aamar")+1);
	
	student -> grades.humanisitic_grades.verbal_grades.hebrew=80;
	student -> grades.humanisitic_grades.verbal_grades.english=90;
	student -> grades.humanisitic_grades.verbal_grades.literature=100;
	
	student -> grades.humanisitic_grades.mind_grades.sociologoy=80;
	student -> grades.humanisitic_grades.mind_grades.psychology=90;
	
	student -> grades.real_grades.nature_grades.biology=70;
	student -> grades.real_grades.nature_grades.physics=60;
	student -> grades.real_grades.nature_grades.chemistry=65;
	
	student -> grades.real_grades.engineering_grades.programming=90;
	student -> grades.real_grades.engineering_grades.electronics=80;
	
	student -> grades.real_grades.math_grade=85;
	
	student -> grades.sports_grade=100;
}


static void ImplementFunc(student_ty* student , student_ty* student2)
{
	FILE *outfile;
	
	assert(NULL != student && NULL != student2);
	
	SaveStudent(outfile,student);
	LoadStudent(outfile,student2);
	TestFunc(student,student2);
	
}

void SaveStudent(FILE* outfile ,student_ty* student)
{
	assert(NULL != student);
	outfile = fopen ("person.dat", "w");
	 
	if (NULL == outfile)
	{
		fprintf(stderr, "\nError opened file\n");
	}else 
	{
		SaveStudentImpl(outfile ,student);
	}
	
	fclose (outfile);
}

void LoadStudent(FILE* file,student_ty* studentload2)
{
	assert( NULL != studentload2);
	
	file=fopen("person.dat", "r");
	
	if (NULL == file) 
	{
		fprintf(stderr, "\nError to read file\n");
	}else
	{
		LoadStudentImpl(file,studentload2);
	}
	
	fclose(file);
}

static void TestFunc(student_ty* student,student_ty* student2)
{
	size_t name_size=strlen(student->first_name);
	
	assert(NULL != student && NULL != student2);
	
	printf("\nAfter uploading struct to binary file & reload it \n from 
	                                binary file to struct the result:\n\n");
	
	if(0 ==  memcmp(student -> first_name, student2 -> first_name,name_size))
	printf("same value of first name       \t%s\n",student2 -> first_name);
	
	if(0 ==  memcmp(student -> last_name, student2 -> last_name,name_size))
	printf("same value of last name       \t%s\n",student2 -> last_name);
	
	if(student2-> grades.humanisitic_grades.verbal_grades.hebrew == 
	   student-> grades.humanisitic_grades.verbal_grades.hebrew)
	printf("same value for hebrew grade    \t%.2f\n",student2-> grades.
					humanisitic_grades.verbal_grades.hebrew);
	
	if(student2 -> grades.humanisitic_grades.verbal_grades.english == 
	   student -> grades.humanisitic_grades.verbal_grades.english)
	printf("same value for english grade  \t%.2f\n",student -> 
				grades.humanisitic_grades.verbal_grades.english);
	
	if(student2 -> grades.humanisitic_grades.verbal_grades.literature == 
	   student -> grades.humanisitic_grades.verbal_grades.literature)
	printf("same value for literature grade  %.2f\n",
	student -> grades.humanisitic_grades.verbal_grades.literature);
	
	if(student2 -> grades.humanisitic_grades.mind_grades.sociologoy == 
	   student -> grades.humanisitic_grades.mind_grades.sociologoy)
	printf("same value for sociologoy grade  %.2f\n",
	student -> grades.humanisitic_grades.mind_grades.sociologoy);
	
	if(student2 -> grades.humanisitic_grades.mind_grades.psychology == 
	   student -> grades.humanisitic_grades.mind_grades.psychology)
	printf("same value for psychology grade  %.2f\n",
	student -> grades.humanisitic_grades.mind_grades.psychology);
	
	if(student2 -> grades.real_grades.nature_grades.biology == 
	   student -> grades.real_grades.nature_grades.biology)
	printf("same value for biology grade   \t%.2f\n",
	student -> grades.real_grades.nature_grades.biology);
	
	if(student2 -> grades.real_grades.nature_grades.physics == 
	   student -> grades.real_grades.nature_grades.physics)
	printf("same value for physics grade   \t%.2f\n",
	student -> grades.real_grades.nature_grades.physics);
	
	if(student2 -> grades.real_grades.nature_grades.chemistry == 
	   student -> grades.real_grades.nature_grades.chemistry)
	printf("same value for chemistry grade   %.2f\n",
	student -> grades.real_grades.nature_grades.chemistry);
	
	if(student2 -> grades.real_grades.engineering_grades.programming == 
	   student -> grades.real_grades.engineering_grades.programming)
	printf("same value for programming grade %.2f\n",
	student -> grades.real_grades.engineering_grades.programming);
	
	if(student2 -> grades.real_grades.engineering_grades.electronics == 
	   student -> grades.real_grades.engineering_grades.electronics)
	printf("same value for electronics grade %.2f\n",
	student -> grades.real_grades.engineering_grades.electronics);
	
	if(student2 -> grades.real_grades.math_grade == 
	   student -> grades.real_grades.math_grade)
	printf("same value for math grade      \t%.2f\n",
	student -> grades.real_grades.math_grade);
	
	if(student2 -> grades.sports_grade == 
	   student -> grades.sports_grade)
	printf("same value for sport grade   \t%.2f\n",
	student -> grades.sports_grade);
	
	exit(1); 	
}

/******************* save student *********************/

static void SaveStudentImpl(FILE* outfile , student_ty* student)
{
	
	SaveStudentName(outfile , student->first_name);
	SaveStudentName(outfile , student->last_name);
	
	SaveStudentGrades(outfile , &student-> grades);	
			
}

static void SaveStudentName(FILE* outfile , char* str_name)
{
	size_t name_size=strlen(str_name)+1;
	
	fwrite(&name_size,sizeof(size_t), 1, outfile);					
	fwrite(str_name,name_size, 1, outfile);					
}

static void SaveStudentGrades(FILE* outfile , student_grades_ty* studentgrade)
{
	fwrite ((float*)&studentgrade->sports_grade , sizeof(student_grades_ty)
								, 1, outfile);
	
	SaveHumanisiticGrades(outfile ,&studentgrade->humanisitic_grades);
	SaveRealGrades(outfile ,&studentgrade->real_grades);
}
static void SaveHumanisiticGrades(FILE* outfile 
					, humansitc_grades_ty* humangrade)
{
	SaveVerbalGrades(outfile , &humangrade->verbal_grades);
	SaveMindGrades(outfile , &humangrade->mind_grades);
}
static void SaveVerbalGrades(FILE* outfile , verbal_grades_ty* verbalgrade)
{
	fwrite ((float*)&verbalgrade->hebrew ,sizeof(verbalgrade->hebrew),
							 1, outfile);
	fwrite ((float*)&verbalgrade->english ,sizeof(verbalgrade->english),
							 1, outfile);
	fwrite ((float*)&verbalgrade->literature ,sizeof(verbalgrade->literature),
							 1, outfile);		
}
static void SaveMindGrades(FILE* outfile, mind_grades_ty* mindgrades)
{
	fwrite ((float*)&mindgrades->sociologoy ,sizeof(mindgrades->sociologoy),
							 1, outfile);
	fwrite ((float*)&mindgrades->psychology ,sizeof(mindgrades->psychology),
							 1, outfile);
}

static void SaveRealGrades(FILE* outfile, real_grades_ty* realgrades)
{
	fwrite ((float*)&realgrades->math_grade ,sizeof(realgrades->math_grade),
							 1, outfile);
	SaveNatureGrades(outfile , &realgrades->nature_grades);
	SaveEngGrades(outfile , &realgrades->engineering_grades);
}

static void SaveNatureGrades(FILE* outfile, nature_grades_ty* naturegrades)
{
	fwrite ((float*)&naturegrades->biology ,sizeof(naturegrades->biology),
							 1, outfile);
	fwrite ((float*)&naturegrades->physics ,sizeof(naturegrades->physics),
							 1, outfile);
	fwrite ((float*)&naturegrades->chemistry 
				,sizeof(naturegrades->chemistry), 1, outfile);
}
static void SaveEngGrades(FILE* outfile, engineering_grades_ty* enggrades)
{
	fwrite ((float*)&enggrades->programming ,sizeof(enggrades->programming),
							 1, outfile);
	fwrite ((float*)&enggrades->electronics,sizeof(enggrades->electronics),
							 1, outfile);
}

/******************* load student *********************/
static void LoadStudentImpl(FILE* outfile , student_ty* student)
{
	LoadStudentName(outfile ,student->first_name);
	LoadStudentName(outfile ,student->last_name);
	
	LoadStudentGrades(outfile ,&student-> grades);				
}

static void LoadStudentName(FILE* outfile , char* str_name)
{

	size_t name_size = 0;

	fread(&name_size,sizeof(size_t), 1, outfile);				
	fread(str_name, name_size, 1, outfile);	
	
				
}

static void LoadStudentGrades(FILE* outfile , student_grades_ty* studentgrade)
{
	fread((float*)&studentgrade->sports_grade , sizeof(student_grades_ty),
								 1, outfile);
	
	LoadHumanisiticGrades(outfile,&studentgrade->humanisitic_grades);
	LoadRealGrades(outfile,&studentgrade->real_grades);
}
static void LoadHumanisiticGrades(FILE* outfile , humansitc_grades_ty* humangrade)
{
	LoadVerbalGrades(outfile , &humangrade->verbal_grades);
	LoadMindGrades(outfile , &humangrade->mind_grades);
}
static void LoadVerbalGrades(FILE* outfile , verbal_grades_ty* verbalgrade)
{
	fread((float*)&verbalgrade->hebrew ,sizeof(verbalgrade->hebrew),
							 1, outfile);
	fread((float*)&verbalgrade->english ,sizeof(verbalgrade->english),
							 1, outfile);
	fread((float*)&verbalgrade->literature ,sizeof(verbalgrade->literature),
							 1, outfile);		
}
static void LoadMindGrades(FILE* outfile, mind_grades_ty* mindgrades)
{
	fread((float*)&mindgrades->sociologoy ,sizeof(mindgrades->sociologoy),
							 1, outfile);
	fread((float*)&mindgrades->psychology ,sizeof(mindgrades->psychology),
							 1, outfile);
}

static void LoadRealGrades(FILE* outfile, real_grades_ty* realgrades)
{
	fread((float*)&realgrades->math_grade ,sizeof(realgrades->math_grade),
							 1, outfile);
	LoadNatureGrades(outfile , &realgrades->nature_grades);
	LoadEngGrades(outfile , &realgrades->engineering_grades);
}

static void LoadNatureGrades(FILE* outfile, nature_grades_ty* naturegrades)
{
	fread((float*)&naturegrades->biology ,sizeof(naturegrades->biology),
							 1, outfile);
	fread((float*)&naturegrades->physics ,sizeof(naturegrades->physics),
							 1, outfile);
	fread((float*)&naturegrades->chemistry ,sizeof(naturegrades->chemistry),
							 1, outfile);
}
static void LoadEngGrades(FILE* outfile, engineering_grades_ty* enggrades)
{
	fread((float*)&enggrades->programming ,sizeof(enggrades->programming),
							 1, outfile);
	fread((float*)&enggrades->electronics,sizeof(enggrades->electronics),
							 1, outfile);
}



