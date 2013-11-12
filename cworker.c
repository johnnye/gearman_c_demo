/******************************************************************************
 *
 * Gearman C Demo
 *
 * Copyright (c) 2012 John Nye - john@nimbleworks.co.uk
 *
 * This is an useless example of how wto build a c gearman worker.
 *
 * I built most of this by examining the source mod_gearman code by
 * Sven Nierlein http://labs.consol.de/nagios/mod-gearman/
 *
 * Released under the MIT License included in this project
 *
 *
 *****************************************************************************/


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libgearman/gearman.h>

void *doing_work(gearman_job_st *job, void *context, size_t *result_size, gearman_return_t *ret_ptr){

	int workloadsize;

    /* contect is unused */
    context = context;
    workloadsize = gearman_job_workload_size(job); //how big is the workload?

	//Copy the workload into a usable string
    char workload[workloadsize];
    strncpy(workload, (const char*)gearman_job_workload(job), workloadsize);
    workload[workloadsize] = '\0';
	//Do your work here
    puts(workload);

	//Not passing any result information back at the moment
    result_size = 0;

	/* Should do some checks to monitor for fails
	* all we're doing here is just printing the workload
	*/
    *ret_ptr = GEARMAN_SUCCESS;

    return 0;
}


int main(void){
    gearman_worker_st worker;

	//Create the worker
	gearman_worker_create(&worker);

	//Connect the worker to the server and chech it worked
    gearman_return_t ret= gearman_worker_add_server(&worker, "localhost", 4730);
    if (gearman_failed(ret)){
        return EXIT_FAILURE;
    }

	//register function, (worker, job_queue_name, timeout, function_to_do_work, context)
    ret = gearman_worker_add_function(&worker,"image",0,doing_work,NULL);
	if(gearman_failed(ret)){
		return EXIT_FAILURE;
	}

	//Infinite loop to keep watching
    while(1){
		//Does the work
        ret = gearman_worker_work(&worker);
        if ( ret != GEARMAN_SUCCESS ) {
            fprintf(stderr,"worker error: %s\n", gearman_worker_error( &worker ) );
            gearman_job_free_all( &worker );
            gearman_worker_free( &worker );
            /* sleep on error to avoid cpu intensive infinite loops */
            sleep(5);
        }
    }
    return EXIT_SUCCESS;
}
