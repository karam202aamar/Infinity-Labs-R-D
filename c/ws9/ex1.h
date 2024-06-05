#ifndef __ILRD_SERIALIZE_STRUCTS__
#define __ILRD_SERIALIZE_STRUCTS__

#define NAME_MAX_LENGTH 20

/* Structs: */

typedef struct VerbalGrades
{
    float hebrew;
    float english;
    float literature;
}verbal_grades_ty;

typedef struct MindGrades
{
    float sociologoy;
    float psychology;
}mind_grades_ty;

typedef struct HumanisticGrades
{
    verbal_grades_ty verbal_grades;
    mind_grades_ty mind_grades;
}humansitc_grades_ty;

typedef struct NatureGrades
{
    float biology;
    float physics;
    float chemistry;
} nature_grades_ty;

typedef struct EngineeringGrades
{
    float programming;
    float electronics;
} engineering_grades_ty;

typedef struct RealGrades /**/
{
    nature_grades_ty nature_grades;
    engineering_grades_ty engineering_grades;
    float math_grade;
}real_grades_ty;

typedef struct StudentGrades
{
    humansitc_grades_ty humanisitic_grades;
    real_grades_ty real_grades;
    float sports_grade;
} student_grades_ty;

typedef struct Student
{
    char first_name[NAME_MAX_LENGTH];
    char last_name[NAME_MAX_LENGTH];
    student_grades_ty grades;
} student_ty;


/* API: */

void SaveStudent(FILE* file,student_ty* student);

void LoadStudent(FILE* file,student_ty* student2);

#endif /*__ILRD_SERIALIZE_STRUCTS__*/












