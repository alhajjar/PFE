function  [alpha3]= coeff_depot3( p,eta)

    a1 = 0.23001;
    a2 = 0.86894;
    a3 = 1.08105;
    k = 8.22311;
    for i=1:196
        for j=1:194
     alpha3(i, j) = log(a2+a1*(p(i,j)-p(i,j)*p(i,j))*atan(k*eta(i,j)))+a3*p(i,j) ;
        end
    end
    
end
    