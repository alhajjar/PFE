function  [alpha5]= coeff_depot5( p,eta)

  a1=-0.12952;
  a2 = 0.73519;
  a3 =1.92703;
  k =38.70085;
    for i=1:196
        for j=1:194
             if (p(i,j)<0.5)
   alpha5(i, j) =  log(a2+a1*(p(i,j)-(p(i,j)*p(i,j))*atan(-k*eta(i,j))+a3*p(i,j))) ;
             else
   alpha5(i, j) = log(a2+a1*(p(i,j)-(p(i,j)*p(i,j))*atan(k*eta(i,j))+a3*p(i,j)));
             end

        end
    end
    
end