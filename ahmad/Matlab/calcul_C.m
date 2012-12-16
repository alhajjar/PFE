function MATRICE_C = calcul_C(h,MATRICE_A,MATRICE_C,coeffdepot2,N1)

    f = 1;

   for i=1:196
            for j=1:194

                vec1(f,1) = MATRICE_C(i,j) + h* coeffdepot2(i,j)* MATRICE_A(i,j);

            f = f +1;
            end
   end

 


    vec_C =  N1\vec1;
    
    f = 1;
    for i = 1:196

      for j = 1:194 
          
       MATRICE_C(i,j) = vec_C(f,1); 
         f = f+1;        
      end
    end
    
 end
  

 
 