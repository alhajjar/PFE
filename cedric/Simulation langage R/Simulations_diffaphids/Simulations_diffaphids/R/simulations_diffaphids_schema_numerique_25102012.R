############################################################################
#        Fonction de rotation 
#retourne la rotation(un quarts de tour dans le sens des aiguilles d'une montre) de la matrice
#
# prend en argument un matrice
#Soit : X				retourne rot(X):
#    1    4    7   10		    3    2    1
#    2    5    8   11		    6    5    4
#    3    6    9   12		    9    8    7
#					   12   11   10
#
############################################################################

rot <- function(x) {
nx <- dim(x)[1]
for (i in 1:(nx%/%2)) {
uu <- x[nx - i + 1, ]
x[nx - i + 1, ] <- x[i, ]
x[i, ] <- uu
}
t(x)
}

#========================================================================================
#
#  SCHEMA NUMERIQUE EXPLICITE
#
#========================================================================================
schema_numerique_explicit=function(A,C,k,h,vitesseh,vitessev,d,r,alpha1,alpha2,MMx,MMy){

A=as.matrix(A)
C=as.matrix(C)


C_o=C_e=C_n=C_s=C
C_o[1,]=0
C_e[MMx,]=0
C_s[1,]=0
C_n[,MMy]=0

dx=dy=k
dt=h

f1=alpha2*A+C*(1-alpha1)	#fonction de reaction de C
C= dt*f1+ C- vitesseh*dt/(dx)*(C-C_o) - vitessev*dt/dy*(C-C_e) + d*dt/(dx*dx)*(C_e+C_o-2*C) + d*dt/(dy*dy)*(C_n+C_s-2*C) 


f2=A*(r-alpha2)+alpha1*C   #fonction de reaction de A
A= dt*f2+ A


return(list(A,C))
}





#========================================================================================
#
#  SCHEMA NUMERIQUE AVEC UN SPLITTING D'OPERATEURS
#
#========================================================================================


schema_numerique_ADI=function(A,C,indice1,indice2,k,h,vitesseh,vitessev,d,r,alpha1,alpha2,MMx,MMy){

A=as.matrix(A)
C=as.matrix(C)

MatA1=1+h*r*(1-alpha2)


#================================================================================
# 1/2 pas horizontal
# Attention a la linearisation de la matrice
# 
#   		a11   a12   a13
#Si Mat=	a21   a22   a23  
#   		a31   a32   a33
#
#alors as.vector(Mat)=c(a11 a21 a31 a12 a22 a32 a13 a23 a33)
#
#
#
#================================================================================

MatA1_vec=as.vector(MatA1)
C_temp_vec=as.vector(C)
A_temp_vec=as.vector(A)
C_vec=as.vector(C)
A_vec=as.vector(A)

##Indice pour les conditions de Dirichlet
#indice1<-which(C_vec==0)


#Diagonale principale
Mat1_temp_diag=1.000+h*alpha1+(2*h*d)/(k^2)   #matrice de taille MMx MMy	
Mat1_temp_diag=as.vector(Mat1_temp_diag)
Mat1_temp_diag[indice1]<-1

#Diagonale inferieure
Mat1_temp_inf=-(h/(k^2))*d-(h/(2*k))*vitesseh  #matrice de taille MMx MMy	
#Mat1_temp_inf[MMx,]=0.0
diag_inf=as.vector(Mat1_temp_inf)
diag_inf[indice1]<-0
diag_inf=diag_inf[-MMx*MMy]

#Diagonale superieure
Mat1_temp_sup=-(h/(k^2))*d+(h/(2*k))*vitesseh  #matrice de taille MMx MMy	
#Mat1_temp_sup[1,]=0.0
diag_sup=as.vector(Mat1_temp_sup)
diag_sup[indice1]<-0
diag_sup=diag_sup[-1]

#construction de la matrice bande
Mat1h=bandSparse(MMx*MMy, k = c(-1:1), diag = list(diag_inf,Mat1_temp_diag
,diag_sup))#, symm=TRUE)

#phi_h_vec=as.vector(h*alpha1*r*C)
fA<-A_vec+as.vector(h*alpha1*r*C)
fA[indice1]<-0
#boo=as.vector(h*alpha2*A)
fC<-C_vec+as.vector(h*alpha2*A)
fC[indice1]<-0

#C_vec=solve(Mat1h,C_vec+boo)
#A_vec=(1/MatA1_vec)*(A_vec+phi_h_vec)
C_vec=solve(Mat1h,fC)
A_vec=(1/MatA1_vec)*(fA)

C=matrix(as.vector(C_vec),nrow=MMx,ncol=MMy)
A=matrix(A_vec,nrow=MMx,ncol=MMy)


#================================================================================
# 1/2 pas vertical
# Attention a la linearisation de la matrice
# 
#   		|a11   a12   a13|
#Si Mat=	|a21   a22   a23|  
#   		|a31   a32   a33|
#
#alors as.vector(unmatrix(Mat,byrow=T))=c(a11 a12 a13 a21 a22 a23 a31 a32 a33)
#
#================================================================================

MatA1_vec=as.vector(unmatrix(MatA1,byrow=T))
C_temp_vec=as.vector(unmatrix(C,byrow=T))
A_temp_vec=as.vector(unmatrix(A,byrow=T))
C_vec=as.vector(unmatrix(C,byrow=T))
A_vec=as.vector(unmatrix(A,byrow=T))

##Indice pour les conditions de Dirichlet
#indice2<-which(C_vec==0)

# Diagonale principale
Mat1_temp_diag=1.0+h*alpha1+(2*h*d)/(k^2)  #matrice de taille MMx MMy	
Mat1_temp_diag<-as.vector(unmatrix(Mat1_temp_diag))
Mat1_temp_diag[indice2]<-1

#Diagonale inferieure
Mat1_temp_inf=-(h/(k^2))*d-(h/(2*k))*vitessev  #matrice de taille MMx MMy	
#Mat1_temp_inf[,MMy]=0
diag_inf=as.vector(unmatrix(Mat1_temp_inf,byrow=T))
diag_inf[indice2]<-0
diag_inf=diag_inf[-MMx*MMy]

#Diagonale superieure
Mat1_temp_sup=-(h/(k^2))*d+(h/(2*k))*vitessev  #matrice de taille MMx MMy	
#Mat1_temp_sup[,1]=0
diag_sup=as.vector(unmatrix(Mat1_temp_sup,byrow=T))
diag_sup[indice2]<-0
diag_sup=diag_sup[-1]

#construction de la matrice bande
Mat1v=bandSparse(MMx*MMy, k = c(-1:1), diag = list(diag_inf,Mat1_temp_diag
,diag_sup))#, symm=TRUE)

#phi_v_vec=as.vector(unmatrix(h*alpha1*r*C,byrow=T))
fA<-A_vec+as.vector(unmatrix(h*alpha1*r*C,byrow=T))
fA[indice2]<-0
#boo=as.vector(unmatrix(h*alpha2*A,byrow=T))
fC<-C_vec+as.vector(unmatrix(h*alpha2*A,byrow=T))
fC[indice2]<-0

#C_vec=solve(Mat1v,C_vec+boo)
#A_vec=(1/MatA1_vec)*(A_vec+phi_v_vec)
C_vec=solve(Mat1v,fC)
A_vec=(1/MatA1_vec)*(fA)

C=matrix(as.vector(C_vec),byrow=T,nrow=MMx,ncol=MMy)
A=matrix(A_vec,byrow=T,nrow=MMx,ncol=MMy)

return(list(A,C))
}
