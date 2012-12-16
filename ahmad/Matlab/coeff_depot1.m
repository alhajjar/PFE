function  [alpha1]= coeff_depot1( p,eta)

    a1 = 1.004855;
    a2 = 1.652655;
    a = -0.267819;
    k = 6.214583;
  
    for i=1:196
        for j=1:194
              alpha1(i, j)=log(a1+a*(-p(i,j)*p(i,j)+p(i,j))*atan(k*eta(i,j))+a2*p(i,j));
        end
    end
    
    end
    