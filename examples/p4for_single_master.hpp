
#pragma once
#include "../include/ompe/omp_log.hpp"

void p4for_single_master()
{
    static int const rep = 3;
    {
        int num_ths = 5;

        omp_set_nested(1);
        omp_set_dynamic(0);

        omp_log_inic();
        #pragma omp parallel num_threads(num_ths)
        {
            omp_log_inic_parented();

            for(int i=0; i < rep; i++)
                omp_log << "simple for " << i << std::endl;

            #pragma omp parallel num_threads(2)
            {
                omp_log_inic_parented();
                #pragma omp single
                {
                    for(int i=0; i < rep; i++)
                        omp_log << "NESTED SINGLE " << i << std::endl;
                }
            }

            #pragma omp master
            {
                for(int i=0; i < rep; i++)
                    omp_log << "MASTER " << i << std::endl;
            }

            #pragma omp single
            {
                for(int i=0; i < rep; i++)
                    omp_log << "SINGLE " << i << std::endl;
            }

            #pragma omp barrier
            
            #pragma omp single
            {
                omp_log << "--barrier-----" << std::endl;
            }
            
            for(int i=0; i < rep; i++)
                omp_log << "parallel 4." << i << std::endl;

        }
    }
}

