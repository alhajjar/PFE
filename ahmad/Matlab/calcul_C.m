function MATRICE_C = calcul_C(h,MATRICE_A,MATRICE_C,coeffdepot2,N1,iteration)


 for it = 1 : iteration
      f = 1;
  for i = 1:196

      for j = 1:194

             vec1(1,f) = MATRICE_C(i,j) + h* coeffdepot2(i,j)* MATRICE_A(i,j);
                 f = f + 1;
      end
  end

  [L,U] = lu(N1);
   LL = inv(L) ;
   N11 = LL / U ;
   
    vec_C =  vec1/N11;
    
    f = 1;
    for i = 1:196

      for j = 1:194 
          
       MATRICE_C(i,j) = vec_C(1,f); 
         f = f+1;        
      end
    end
    
 end
  

 
 