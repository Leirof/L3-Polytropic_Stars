int lane_emden(size_t* nx, double** x, double** theta, double n, double dx){
	int ierr;
	size_t size = *nx;
	double dx2 = dx * dx;
	
	double A = 0, B = 0;
	
	/* TODO : you might need some definitions */
	(*theta)[0] = 1;
	(*theta)[1] = 1;
	(*x)[0] = -1.0/2 * dx;
	
	export_theta_i(0, 1.0, FALSE);
	export_theta_i(1, 1.0, TRUE);
	
	double cpt = 0;
	printf("x: %lf\n", (*x)[0]);
	
	for (size_t i = 1; i < *nx; ++i){
		cpt++;		
		(*x)[i] = (cpt - 1.0/2)*dx;
		/* If we reach the size of the arrays , we need to re- allocate memory */
		if(i >= size - 2){
			/* We increase the size by a factor REALLOC_FATOR) */
			size_t new_size = (size_t) (size * REALLOC_FACTOR);
			ierr = resize(new_size, x);
			/* Checking i f memory could be allocated */
			if(!ierr){
				return ierr;
			}
			/* Checking i f memory could be allocated */
			ierr = resize(new_size, theta );
			if(!ierr){
				return ierr;
			}
			size = new_size;
		}
		
		/* 2nd order numerical scheme */
		
		A = 1/((1 + dx / (2 * (*x)[i] ))
			*( 1 + dx / (2 * (*x)[i] )));
        B = (1 - dx / ( 2 * (*x)[i] ))
			*(1 - dx / ( 2 * (*x)[i] ));
        
        
        (*theta)[i + 1] = (*theta)[i] + A * (B * ((*theta)[i] - (*theta)[i - 1]) - dx2 * pow((*theta)[i], (double) n)); /* DONE ? : you need to code the scheme here */
        
		printf("i: %d   nx: %d   x: %lf   theta[i+1]: %lf\n", (int) i, (int) *nx, (*x)[i], (*theta)[i + 1]);
		printf("   A: %lf   B: %d\n", A, B);
        printf("   theta^n: %lf\n", pow((*theta)[i], (double) n));
        
        export_theta_i(cpt, (*theta)[i+1], TRUE);
	
		/* We reached the outer boundary */
		
		if((*theta) [i + 1] <= 0.){
			*nx = i + 2;
			/* We realloc again to the actual size , in order to free the useless memory */
			ierr = resize(*nx, x);
			if (!ierr ){
				return ierr;
			}
			ierr = resize(*nx, theta );
			if(!ierr){
				return ierr;
			}
			break;
		}
	}
	return TRUE;
}