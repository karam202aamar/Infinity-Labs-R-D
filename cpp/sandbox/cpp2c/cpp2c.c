/******************************************************************************/
// Project: cpp2c
// Date:
// Author: karam aamar
// Reviewer: karin brukhis
// Version: 1.0
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
/******************************************************************************/
#define TEMPLATE_MAX(T, t1, t2)  \
    ({                           \
        T t1_ = (t1);            \
        T t2_ = (t2);            \
        (t1_ > t2_ ? t1_ : t2_); \
    })
/******************************************************************************/
typedef struct PublicTransport PT_ty;
typedef struct Minibus         MB_ty;
typedef struct Taxi            Taxi_ty;
typedef struct SpecialTaxi     SpecialTaxi_ty;
typedef struct PublicConvoy    PublicConvoy_ty;

typedef struct PublicTransport_vtable VTablePTrans_ty;
typedef struct Minibus_vtable         VTableMinibus_ty;
typedef struct Taxi_vtable            VTableTaxi_ty;
typedef struct PublicConvoy_vtable    VTablePublicConvoy_ty;
/********************************define structs********************************/
struct PublicTransport
{
    void *vptr;
    int m_license_plate;
};

struct Minibus
{
    PT_ty public_t;
    int m_numSeats;
};

struct Taxi
{
    PT_ty public_t;
};

struct SpecialTaxi
{
    Taxi_ty taxi;
};

struct PublicConvoy
{
    PT_ty public_t;
    PT_ty *m_pt1;
    PT_ty *m_pt2;
    MB_ty m_m;
    Taxi_ty m_t;
};
/****************************define global counter*****************************/
static int s_count = 0;
/**************************define structs of vtables***************************/
struct PublicTransport_vtable
{
    void (*display)(PT_ty *);
    void (*dtor)(PT_ty *);
};

struct Minibus_vtable
{
    void (*display)(MB_ty *);
    void (*dtor)(MB_ty *);
    /* void (*wash)(MB_ty *, int); */
};

struct Taxi_vtable
{
    void (*display)(Taxi_ty *);
    void (*dtor)(Taxi_ty *);
};

struct PublicConvoy_vtable
{
    void (*display)(PublicConvoy_ty *);
    void (*dtor)(PT_ty *);
};

/****************************vtable declaration********************************/
VTablePTrans_ty vtable_pub_trans;
VTableMinibus_ty vtable_minibus;
VTableTaxi_ty vtable_taxi;
VTablePublicConvoy_ty vtable_public_convoy;

/*******************public transportation methods definitions******************/
void Ctor_PublicTransport(PT_ty *this) // v
{
    ++s_count;
    this->m_license_plate = s_count;
    this->vptr = &vtable_pub_trans;
    printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
}

void Dtor_PublicTransport(PT_ty *this) // v
{
    --s_count;
    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}

void CCtor_PublicTransport(PT_ty *this, PT_ty *other) // v
{
    this->m_license_plate = ++s_count;
    this->vptr = &vtable_pub_trans;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void PublicTransportDisplay(PT_ty *this) // v
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}
/***********************************minibus************************************/
void Ctor_MiniBus(MB_ty *this) // v
{
    Ctor_PublicTransport(this);
    printf("Minibus::Ctor()\n");
    (this->public_t).vptr = &vtable_minibus;
    this->m_numSeats = 20;
}

void CCtor_MiniBus(MB_ty *this, MB_ty *other) // v
{
    CCtor_PublicTransport(&this->public_t, &other->public_t);
    this->m_numSeats = other->m_numSeats;
    this->public_t.vptr = &vtable_minibus;
    printf("Minibus::CCtor()\n");
}

void Dtor_MiniBus(MB_ty *this) // v
{
    printf("Minibus::Dtor()\n");
    Dtor_PublicTransport(&this->public_t);
}

void MinibusDisplay(MB_ty *this) // v
{
    printf("Minibus::display() ID:%d", get_ID((PT_ty *)(this)));
    /* printf(" num seats:%d\n", this->m_numSeats); */
}

void MinibusWash(MB_ty *this, int minutes) // v
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, get_ID((PT_ty *)(this)));
}
/**************************************taxi************************************/
void TaxiConstructor(Taxi_ty *this) // v
{
    Ctor_PublicTransport(this);
    /*set the vptr to vtable_taxi*/
    (this->public_t).vptr = &vtable_taxi;
    printf("Taxi::Ctor()\n");
}

void TaxiCpyConstructor(Taxi_ty *this, Taxi_ty *other) // v
{
    CCtor_PublicTransport((PT_ty *)this, (PT_ty *)other);
    this->public_t.vptr = &vtable_taxi;
    printf("Taxi::CCtor()\n");
}

void TaxiDestructor(Taxi_ty *this) // v
{
    printf("Taxi::Dtor()\n");
    Dtor_PublicTransport(&this->public_t);
}

void TaxiDisplay(Taxi_ty *this) // v
{
    printf("Taxi::display() ID:%d\n", get_ID((PT_ty *)(this)));
}
/********************************special taxi**********************************/
void SpecialTaxiConstructor(SpecialTaxi_ty *this) // v
{
    TaxiConstructor(this);
    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxiCpyConstructor(SpecialTaxi_ty *this, SpecialTaxi_ty *other) // v
{
    TaxiCpyConstructor((Taxi_ty *)this, (Taxi_ty *)other);
    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxiDestructor(SpecialTaxi_ty *this) // v
{
    printf("SpecialTaxi::Dtor()\n");
    TaxiDestructor(&this->taxi);
}

void SpecialTaxiDisplay(SpecialTaxi_ty *this) // v
{
    printf("SpecialTaxi::display() ID:%d\n", get_ID((PT_ty *)(this)));
}
/****************************phase 2 public convoy*****************************/
void PublicConvoyConstructor(PublicConvoy_ty *this) // v
{
    (this->public_t).vptr = &vtable_public_convoy;

    Ctor_PublicTransport(&this->public_t);

    this->m_pt1 = (MB_ty *)malloc(sizeof(MB_ty));
    this->m_pt2 = (Taxi_ty *)malloc(sizeof(Taxi_ty));
    /*cal ctors*/
    Ctor_MiniBus((MB_ty *)this->m_pt1);
    TaxiConstructor((Taxi_ty *)this->m_pt2);

    Ctor_MiniBus(&this->m_m);
    TaxiConstructor(&this->m_t);
}

void PublicConvoyCpyConstructor(PublicConvoy_ty *this, PublicConvoy_ty *other) // 
{
    CCtor_PublicTransport(this, other);

    this->public_t.vptr = &vtable_public_convoy;

    this->m_pt1 = (MB_ty *)malloc(sizeof(MB_ty));
    CCtor_MiniBus(this->m_pt1, other->m_pt1);

    this->m_pt2 = (Taxi_ty *)malloc(sizeof(Taxi_ty));
    TaxiCpyConstructor(this->m_pt2, other->m_pt2);

    Ctor_MiniBus(&this->m_m);
    TaxiConstructor(&this->m_t);
}

void PublicConvoyDestructor(PublicConvoy_ty *this) // v
{
    VTablePublicConvoy_ty *vtable;

    vtable = (this->m_pt1)->vptr;
    vtable->dtor(this->m_pt1);
    free(this->m_pt1);

    vtable = (this->m_pt2)->vptr;
    vtable->dtor(this->m_pt2);
    free(this->m_pt2);

    Dtor_MiniBus(&this->m_t);
    Dtor_MiniBus(&this->m_m);

    Dtor_PublicTransport(&this->public_t);
}

void PublicConvoyDisplay(PublicConvoy_ty *this) // v
{
    VTablePublicConvoy_ty *vtable;
    vtable = (this->m_pt1)->vptr;
    vtable->display(this->m_pt1);

    vtable = (this->m_pt2)->vptr;
    vtable->display(this->m_pt2);

    MinibusDisplay(&this->m_m);
    TaxiDisplay(&this->m_t);
}
/*****************************more functions to be used************************/
void print_count()
{
    printf("s_count: %d\n", s_count);
} 

int get_ID(PT_ty *this)
{
    return this->m_license_plate;
}

void print_info(PT_ty* pt_)
{
    ((VTablePTrans_ty*)pt_->vptr)->display(pt_);
}

void print_info_public_tras(PT_ty *a)
{
    PublicTransportDisplay(a);
}

void print_info_minibus(MB_ty *m)
{
    MinibusWash(m, 3);
}

PT_ty print_info_i(int i)
{
    MB_ty temp_m;
    PT_ty ret;

    Ctor_MiniBus(&temp_m);
    printf("print_info(int i)\n");
    ((VTableMinibus_ty*)(temp_m.public_t.vptr))->display(&temp_m);
    /*use cpy ctr for public trans*/
    CCtor_PublicTransport(&ret, &temp_m.public_t);
    ((VTableMinibus_ty*)(temp_m.public_t.vptr))->dtor(&temp_m);   
    
    return ret;
}

void taxi_display(Taxi_ty* taxi_)
{
    Taxi_ty tmp_taxi;
    TaxiCpyConstructor(&tmp_taxi, taxi_);
    ((VTableTaxi_ty *)((taxi_->public_t)).vptr)->display(taxi_);
}
/******************************************************************************/

/******************************************************************************/
int main()
{
    /*init vtables*/
    /*public transportation*/
    vtable_pub_trans.display = PublicTransportDisplay;
    vtable_pub_trans.dtor = Dtor_PublicTransport;
    /*minibus*/
    vtable_minibus.display = MinibusDisplay;
    vtable_minibus.dtor = Dtor_MiniBus;
    /*taxi*/
    vtable_taxi.display = TaxiDisplay;
    vtable_taxi.dtor = TaxiDestructor;
    /*phase 2 - public convoy*/
    vtable_public_convoy.display = PublicConvoyDisplay;
    vtable_public_convoy.dtor = PublicConvoyDestructor;
    /*************/

    MB_ty m;
    int i = 0;

    Ctor_MiniBus(&m);
    print_info_minibus(&m);
    PT_ty temp = print_info_i(3);

    
    ((VTablePTrans_ty*)temp.vptr)->display(&temp);
    ((VTablePTrans_ty*)temp.vptr)->dtor(&temp);

    MB_ty* mb_tmp = (MB_ty*)malloc(sizeof(MB_ty));
    Ctor_MiniBus(mb_tmp);

    Taxi_ty* t_tmp = (Taxi_ty*)malloc(sizeof(Taxi_ty));
    TaxiConstructor(t_tmp);
    
    MB_ty* mb2_tmp = (MB_ty*)malloc(sizeof(MB_ty));
    Ctor_MiniBus(mb2_tmp);

    PT_ty* trans_arr[] = {mb_tmp, t_tmp, mb2_tmp};

    for(i = 0; i < 3; ++i)
    {
        print_info(trans_arr[i]);
    }
    for(i = 0; i < 3; ++i)
    {
        ((VTablePTrans_ty*)(trans_arr[i]->vptr))->dtor(trans_arr[i]);
        free(trans_arr[i]);
        trans_arr[i] = NULL;
    }
    PT_ty* arr[3];
    MB_ty m_temp2;
    Ctor_MiniBus(&m_temp2);
    CCtor_PublicTransport(arr, &m_temp2.public_t);
    ((VTableMinibus_ty*)(m_temp2.public_t.vptr))->dtor(&m_temp2);

    Taxi_ty t_temp2;
    TaxiConstructor(&t_temp2);
    CCtor_PublicTransport(arr + 1, &t_temp2.public_t);
    ((VTableTaxi_ty*)t_temp2.public_t.vptr)->dtor(&t_temp2);

    Ctor_PublicTransport(arr + 2);
    #if 0
    
    MB_ty arr3[4];
    for(i = 0; i < 4; ++i)
    {
        Ctor_MiniBus(&arr3[i]);
    }

    Taxi_ty *arr4[4];

    for(i = 0; i < 4; ++i)
    {
        arr4[i] = (Taxi_ty *)malloc(sizeof(Taxi_ty));
        TaxiConstructor(arr4[i]);
    }
    i = 3;
    while(i >= 0)
    {
        TaxiDestructor(arr4[i]);
        free(arr4[i]);
        --i;
    } 

    printf("%d\n", TEMPLATE_MAX(int, 1, 2));
    printf("%d\n", TEMPLATE_MAX(int, 1, 2.0f));

    SpecialTaxi_ty st;
    SpecialTaxiConstructor(&st);
    taxi_display(st.taxi);

    SpecialTaxiDestructor(&st);
    for(i = 3; i >= 0; i--)
    {
        Dtor_MiniBus(&arr3[i]);
    }
    Dtor_MiniBus(&m2);
    for(i = 2; i >= 0; --i)
    {
        Dtor_PublicTransport(&arr2[i]);
    }
    Dtor_MiniBus(&m);
    
    /* VTablePublicConvoy* vtable_convoy;
    PublicConvoy_ty *ts1 = (PublicConvoy_ty *)malloc(sizeof(PublicConvoy_ty));
    PublicConvoyConstructor(ts1);
    PublicConvoy_ty *ts2 = (PublicConvoy_ty *)malloc(sizeof(PublicConvoy_ty));
    PublicConvoyConstructor(ts2);

    vtable_convoy = (ts1->public_t).vptr;
    vtable_convoy->display(ts1);
    vtable_convoy = (ts2->public_t).vptr;
    vtable_convoy->display(ts2);

    vtable_convoy = (ts1->public_t).vptr;
    free(ts1);
    
    vtable_convoy = (ts2->public_t).vptr;
    vtable_convoy->display(ts2);
    free(ts2);  */

    #endif
    return 0;
}


