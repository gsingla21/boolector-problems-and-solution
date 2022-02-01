void sudoku()
{
    Btor *btor=boolector_new();
    boolector_set_opt(btor,BTOR_OPT_MODEL_GEN,1);
    boolector_set_opt(btor,BTOR_OPT_OUTPUT_NUMBER_FORMAT,2);
    BoolectorSort sort_index=boolector_bitvec_sort(btor,8);
    BoolectorSort sort_elem=boolector_bitvec_sort(btor,8);
    BoolectorSort sort_d1_array=boolector_array_sort(btor,sort_index,sort_elem);

    BoolectorNode *grid=boolector_array(btor,sort_d1_array,"grid");


    BoolectorNode *assign[9];

    for(int i=0;i<9;i++)
    {
        assign[i]=boolector_int(btor,i+1,sort_elem);
    }

    BoolectorNode *index[9][9];
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            index[i][j]=boolector_int(btor,i*9+j,sort_elem);
        }
    }

    BoolectorNode *grid2;
    grid2=boolector_write(btor,grid,index[0][6],assign[7]);
    boolector_release(btor,grid);

    grid=boolector_write(btor,grid2,index[1][1],assign[3]);
    boolector_release(btor,grid2);

    grid2=boolector_write(btor,grid,index[1][2],assign[5]);
    boolector_release(btor,grid);

    grid=boolector_write(btor,grid2,index[1][3],assign[0]);
    boolector_release(btor,grid2);

    grid2=boolector_write(btor,grid,index[2][2],assign[4]);
    boolector_release(btor,grid);

    grid=boolector_write(btor,grid2,index[2][3],assign[2]);
    boolector_release(btor,grid2);

    grid2=boolector_write(btor,grid,index[2][5],assign[7]);
    boolector_release(btor,grid);

    grid=boolector_write(btor,grid2,index[3][0],assign[8]);
    boolector_release(btor,grid2);

    grid2=boolector_write(btor,grid,index[3][3],assign[3]);
    boolector_release(btor,grid);

    grid=boolector_write(btor,grid2,index[3][6],assign[6]);
    boolector_release(btor,grid2);
    
    grid2=boolector_write(btor,grid,index[3][8],assign[2]);
    boolector_release(btor,grid);

    grid=boolector_write(btor,grid2,index[4][1],assign[1]);
    boolector_release(btor,grid2);

    grid2=boolector_write(btor,grid,index[4][7],assign[8]);
    boolector_release(btor,grid);

    grid=boolector_write(btor,grid2,index[4][8],assign[3]);
    boolector_release(btor,grid2);

    grid2=boolector_write(btor,grid,index[5][0],assign[2]);
    boolector_release(btor,grid);

    grid=boolector_write(btor,grid2,index[5][6],assign[5]);
    boolector_release(btor,grid2);

    grid2=boolector_write(btor,grid,index[6][3],assign[4]);
    boolector_release(btor,grid);

    grid=boolector_write(btor,grid2,index[7][2],assign[7]);
    boolector_release(btor,grid2);

    grid2=boolector_write(btor,grid,index[7][6],assign[2]);
    boolector_release(btor,grid);

    grid=boolector_write(btor,grid2,index[7][8],assign[0]);
    boolector_release(btor,grid2);

    grid2=boolector_write(btor,grid,index[8][4],assign[1]);
    boolector_release(btor,grid);

    grid=boolector_write(btor,grid2,index[8][5],assign[6]);
    boolector_release(btor,grid2);

    BoolectorNode *readj,*readk,*u1;

    BoolectorNode *_1=boolector_int(btor,1,sort_elem);
    BoolectorNode *_9=boolector_int(btor,9,sort_elem);

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            readj=boolector_read(btor,grid,index[i][j]);
            u1=boolector_ugte(btor,readj,_1);
            boolector_assert(btor,u1);
            boolector_release(btor,u1);
            u1=boolector_ulte(btor,readj,_9);
            boolector_assert(btor,u1);
            boolector_release(btor,u1);
            boolector_release(btor,readj);
        }
    }

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            readj=boolector_read(btor,grid,index[i][j]);
            for(int k=0;k<9 && j!=k;k++)
            {
                readk=boolector_read(btor,grid,index[i][k]);
                u1=boolector_ne(btor,readj,readk);
                boolector_assert(btor,u1);
                boolector_release(btor,readk);
                boolector_release(btor,u1);
            }
            boolector_release(btor,readj);
        }
    }

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            readj=boolector_read(btor,grid,index[j][i]);
            for(int k=0;k<9 && j!=k;k++)
            {
                readk=boolector_read(btor,grid,index[k][i]);
                u1=boolector_ne(btor,readj,readk);
                boolector_assert(btor,u1);
                boolector_release(btor,readk);
                boolector_release(btor,u1);
            }
            boolector_release(btor,readj);
        }
    }  
    
    BoolectorNode *readij,*readwk;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            readij=boolector_read(btor,grid,index[i][j]);
            for(int w=0;w<9;w++)
            {
                for(int k=0;k<9;k++)
                {
                    if(i!=w && j!=k && i/3==w/3 && j/3==k/3)
                    {
                        readwk=boolector_read(btor,grid,index[w][k]);
                        u1=boolector_ne(btor,readij,readwk);
                        boolector_assert(btor,u1);
                        boolector_release(btor,readwk);
                        boolector_release(btor,u1);
                    }
                }
            }
            boolector_release(btor,readij);
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

    //boolector_print_model(btor,"btor",stdout);

    int counti=0;
    for(int i=0;i<9;i++)
    {
        ++counti;
        int countj=0;
        for(int j=0;j<9;j++)
        {
            countj++;
            readij=boolector_read(btor,grid,index[i][j]);
            const char *s=boolector_bv_assignment(btor,readij);
            cout<<s<<" ";
            if(countj==3)
            {
                cout<<" | ";
                countj=0;
            }
            boolector_free_bv_assignment(btor,s);
            boolector_release(btor,readij);
        }
        cout<<endl;
        if(counti==3)
        {
            for(int i=0;i<12;i++)
            {
                cout<<" - ";
            }
            cout<<endl;
            counti=0;
        }
    }
    boolector_release_all(btor);
    boolector_delete(btor);
    return;

}
