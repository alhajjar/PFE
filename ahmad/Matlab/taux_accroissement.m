function  [taux]= taux_accroissement( theta,stades)
     sm = 15.27211;
     b = 0.04133;
     k = 0.11987;
     a1 = -0.10373;
     a2 = 0.11132;

    for i=1:196
            for j=1:194
                    if(theta(i,j)>=30||stades(i,j)>=92)
                        taux(i, j)= 0;
                    else
                        num = a1*log(30-theta(i,j))+a2*log(92-stades(i,j));
                        den = 1+exp(-k*(stades(i,j)-sm))+exp(-b*theta(i,j));
                        taux(i, j)= num/den;
                    end
            end
    end
    