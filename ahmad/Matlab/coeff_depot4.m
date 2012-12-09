function  [alpha4]= coeff_depot4( p,eta)

    a1=0.318941;
    a2=0.983375;
    a3=1.669692;
    k =-6.572036;
    for i=1:196
        for j=1:194
     alpha4(i,j) =log(a2+a1*(p(i,j)-(p(i,j)*p(i,j)))*atan(k*eta(i,j))+a3*p(i,j));
        end
    end
    
end