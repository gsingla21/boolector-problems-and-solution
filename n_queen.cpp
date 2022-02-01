void n_queen()
{
    cout<<"Enter no. of Queens: ";
    int n;
    cin>>n;

    Btor *btor=boolector_new();
    boolector_set_opt(btor,BTOR_OPT_MODEL_GEN,1);
    
    //boolector_set_opt(btor,BTOR_OPT_OUTPUT_NUMBER_FORMAT,0);
    BoolectorSort sort_index=boolector_bitvec_sort(btor,8);
    BoolectorSort sort_elem=boolector_bitvec_sort(btor,n);
    BoolectorSort sort_d1_array=boolector_array_sort(btor,sort_index,sort_elem);

    BoolectorNode *index[n];

    for(int i=0;i<n;i++)
    index[i]=boolector_int(btor,i,sort_index);

    BoolectorNode *array_1d=boolector_array(btor,sort_d1_array,0);

    BoolectorNode *_1=boolector_int(btor,1,sort_elem);
    BoolectorNode *_0=boolector_zero(btor,sort_elem);
    BoolectorNode *_n=boolector_int(btor,n-1,sort_elem);

    //each unique value
    BoolectorNode *read,*u1;
    for(int i=0;i<n;i++)
    {
        read=boolector_read(btor,array_1d,index[i]);
        u1=boolector_ugte(btor,read,_0);
        boolector_assert(btor,u1);
        boolector_release(btor,u1);

        u1=boolector_ulte(btor,read,_n);
        boolector_assert(btor,u1);

        boolector_release(btor,u1);
        boolector_release(btor,read);
    }    
    
    BoolectorNode *readi,*readj,*distinct;
    for(int i=0;i<n;i++)
    {
        readi=boolector_read(btor,array_1d,index[i]);
        for(int j=0;j<n;j++)
        {
            if(i!=j)
            {
                readj=boolector_read(btor,array_1d,index[j]);
                distinct=boolector_ne(btor,readi,readj);
                boolector_assert(btor,distinct);
                boolector_release(btor,distinct);
                boolector_release(btor,readj);
            }
        }
        boolector_release(btor,readi);
    }

    //diagonal queens
    BoolectorNode *sub,*usubo,*temp;
    for(int i=0;i<n-1;i++)
    {
        readi=boolector_read(btor,array_1d,index[i]);
        for(int j=i+1;j<n;j++)
        {
            if(i!=j)
            {
                readj=boolector_read(btor,array_1d,index[j]);
                sub=boolector_sub(btor,readi,readj);
                u1=boolector_int(btor,i-j,sort_elem);
                temp=boolector_ne(btor,sub,u1);
                boolector_assert(btor,temp);
                boolector_release(btor,temp);
                boolector_release(btor,u1);

                u1=boolector_int(btor,j-i,sort_elem);
                temp=boolector_ne(btor,sub,u1);
                boolector_assert(btor,temp);
                boolector_release(btor,temp);
                boolector_release(btor,u1);

                // usubo=boolector_usubo(btor,readi,readj);
                // temp=boolector_not(btor,usubo);
                // boolector_assert(btor,temp);
                // boolector_release(btor,sub);
                // boolector_release(btor,usubo);
                // boolector_release(btor,temp);
                // boolector_release(btor,readj);
            }
        }
    }

    int result=boolector_sat(btor);
    if(result==BOOLECTOR_SAT)
    cout<<"SAT"<<endl;
    else if(result==BOOLECTOR_UNSAT)
    cout<<"UNSAT"<<endl;
    else
    cout<<"OTHER"<<endl;
    
    if(result==BOOLECTOR_UNSAT)
    {
        boolector_release_all(btor);
        boolector_delete(btor);
        return;
    }

    BoolectorNode *sll;
    for(int i=0;i<n;i++)
    {
        read=boolector_read(btor,array_1d,index[i]);
        sll=boolector_sll(btor,_1,read);
        const char *s=boolector_bv_assignment(btor,sll);
        cout<<"s["<<i<<"]: "<<s<<endl;
        boolector_free_bv_assignment(btor,s);
        boolector_release(btor,read);
    }

    boolector_release_all(btor);

    boolector_delete(btor);

    return;
}
