#===============================================================================================
#==============chargement des packages dont on aura besoin======================================
#===============================================================================================

library(Matrix)
library(gdata)
library(tcltk)
library(maptools)
library(geoR)
library(maptools)
library(fBasics)
require(mgcv)

#==============================================================================================
#==============================================================================================
#========= DEBUT ALGO =========================================================================
# Equation KPP en deux dimensions, conditions de Dirichlet et de Neumann
# methode implicite en directions alternees (operator splitting)
# méthodes des différences finies
#==============================================================================================
#==============================================================================================
#diffaphids =function(nc,x_grid_5km,y_grid_5km,p,eta,temper,stades,vent,Date,annee, k, h, date_semis, grtype = "bitmap",initial,bords){

diffaphids<-function(k, h,dd,vitesse=130,grtype = "bitmap",annee=2000){


#==============================================================================================================
#=======EXPLICATION DES PARAMETRES D'ENTREE ===================================================================
#==============================================================================================================
#	nc=shapefile de la France: shapefile
#	temper=les données de températures: matrice de reels
#	stades=les données de stades phenolgiques disponibles: matrice de reels
#	vent=les données de vent disponibles: matrice de reels
#	p=la proportion de ble en tout point(variant de 0 a 1): matrice de reels
#	eta=la distribution des parcelles de ble(variant de -1 a 1): matrice de reels
#	Date= la date de debut des simulations
#	annee=l'annee des simulations: entier
#	k=le pas d'espace: entier
#	h=le pas de temps: entier
#	grtype = "bitmap"
#	initial= les conditions initiales de notre modele: matrice de reels
#	bords=les conditions aux bords de notre modele: matrice de reels

#==============================================================================================================
#=======CREATION DE LA CARTE DE FRANCE ========================================================================
#==============================================================================================================
# creation la bounding box
ncbb <- bbox(nc)
xymin <- ncbb[,1]
xmin_grid=ncbb[1,1]
xmax_grid=ncbb[1,2]
ymin_grid=ncbb[2,1]
ymax_grid=ncbb[2,2]
pixel=k*1000
x_grid = seq(xmin_grid, xmax_grid - pixel, pixel)
y_grid = seq(ymin_grid, ymax_grid - pixel, pixel)
r_xy <- apply(ncbb, 1, diff)
resol <- pixel 

# utilisation taille bb et resolution pour definir le nbre de pixels
ncells <- ceiling(r_xy/resol)

# creation d'une grille en fonction du nombre de pixels
grd <- GridTopology(cellcentre.offset=xymin, cellsize=c(resol, resol), 
  cells.dim=ncells)

# translation des points pour affichage et traitements pour l'interpolation
#xs_grid=c()
#ys_grid=c()
#for (j in y_grid[length(y_grid):1])
#  {
#    for (i in x_grid[length(x_grid):1])
#      {
#        xs_grid=c(i,xs_grid)
#        ys_grid=c(j,ys_grid)
#      }
#  }

#coordonnees des pixels
xs_grid<-x_grid_5km
ys_grid<-y_grid_5km
coord_ttes<-cbind(as.vector(xs_grid),as.vector(ys_grid))

# recuperer uniquement les points qui sont dans la france pour l'affichage et certains traitements
real=overlay(SpatialPoints(coord_ttes),nc)
index=which(!is.na(real))


time.init=Sys.time()


bases_temp=as.matrix(temperature)
coord_villes=as.matrix(coord_villes_temp[,2:3])

#==========================================================================
#       Parametres du schema numerique
#==========================================================================

nx = ncells[1]
ny = ncells[2]
MMx=length(x_grid)
MMy=length(y_grid)
M2=MMx*MMy
M2_bis=M2-1
xmin = 0
xmax = xmin + k * nx
ymin = 0
ymax = ymin + k * ny
x = seq(xmin, xmax - k, k)
y = seq(ymin, ymax - k, k)


dd=0.4			#coefficient de diffusion
vitesseh=0.1	  	# composante horizontale de la vitessse
vitessev=0.2 		# composante verticale de la vitessse
alpha11=0.2			# coefficient d'atterrissage
alpha22=0.5			# coefficient d'envol
rr=0.12   			#taux d'accroissement

d=matrix(dd,nrow=MMx,ncol=MMy)

ind_annee<-which(bases_temp[,2]==annee)


#donnees_temp<-cbind(coord_villes_connues,t(as.matrix(bases_temp[ind_annee,3:dim(bases_temp)[2]])))
donnees_temp<-as.matrix(cbind(coord_villes,t(bases_temp[ind_annee,3:dim(bases_temp)[2]])))



# Voronoi de temperature et de stades pour l'annee "n"
voronoi_temp=realiser_voronoi2(coord_ttes,donnees_temp)
#voronoi_stades=realiser_voronoi1(coord_ttes,donnees_stades)

#Conditions initiales: on annule le nombre d'ailes a la fin de l'hiver
A0 = matrix(0.0001,nrow=MMx,ncol=MMy)  
C0 = matrix(0,nrow=MMx,ncol=MMy)  

Mx3<-MMx/3
My3<-MMy/3

A0[1:Mx3,]<-0.1

AA<-c(A0)
CC<-c(C0)

#Indice des pixels hors de la France (peut etre ameliore):
#indice1 pour le pas horizontal et indice2 pour le pas vertical
AA[-index]=0
indice1<-which(AA==0)

AAA<-matrix(AA,nrow=MMx,ncol=MMy)
AAA<-as.vector(unmatrix(AAA,byrow=T))
indice2<-which(AAA==0)

A0 = matrix(AA,nrow=MMx,ncol=MMy)  


## Affichage de la carte de France pour les conditions initiales
plot(xs_grid,ys_grid,col=as.vector(A0),main="Initial Conditions")
plot(nc,add=T)

C=C0
A=A0

#==========================================================================
#       Edition des parametres a  l'ecran
#==========================================================================
cat("Pas d'espace = ", k, " km ", "\n")
cat("Pas de temps = ", h, " jours ", "\n")
cat("diffusion = ", dd, "\n")
cat("Annee = ", annee, "\n")
cat("Vitesse vent horizontal = ", vitesseh, "\n")
cat("Vitesse vent vertical = ", vitessev, "\n")

#==========================================================================
#       Boucle de diffusion-reaction
#==========================================================================

##Dates de debut et fin de boucle
deb=32		# le 1er fevrier
fin=deb+90		# le modele tourne pendant 3 mois (90 jours)

vec=seq(deb,fin,h)
if (vec[length(vec)]!=fin)
vec=c(vec,fin)

#--------------------------------------------------------------------------------------------
#boucle
#--------------------------------------------------------------------------------------------
for (i in vec){
#print(i)

# i correspond a un jour bien precis de "annee"
ii=2+i

#creation de la matrice des temperatures par voronoi pour le jour "i"
temp=matrix(voronoi_temp[,ii],nrow=MMx,ncol=MMy)
#temp=affect_val(mat2,coord_ind,coord_villes)

#creation de la matrice des stades phenologiques par voronoi pour le jour "i"
#stades=matrix(voronoi_stades[,ii],nrow=MMx,ncol=MMy)
#stades=affect_val(mat3,coord_ind,coord_villes)
stades=matrix(75,nrow=MMx,ncol=MMy)

#coefficient de depot
#a1 =1.004855
#a2 =1.652655
#a =-0.267819
#k  =6.214583
#alpha1= log(a1+a*(-p^2+p)*atan(k*eta)+a2*p)
alpha1=matrix(alpha11,nrow=MMx,ncol=MMy)

#Taux d'accroissement
#s =15.27211
#b =0.04133
#k =0.11987
#a1=-0.10373
#a2=0.11132
#r<-(a1*log(30-temp)+a2*log(92-stades))/(1+exp(-k*(stades-s))+exp(-b*(temp)))
r=matrix(rr,nrow=MMx,ncol=MMy)#0.12

#coefficient d'envol
#a=0.034733
#a0=1.417143
#a1=0.048163
#a2=-0.543663
#logN4=exp(a*stades)/(1+exp(a0+a1*stades+a2*log(1+A)))
#phi_alpha2=2/( 1 + exp( - 0.1 * temp)) - 1
#alpha2=exp(logN4)*phi_alpha2
alpha2=matrix(alpha22,nrow=MMx,ncol=MMy)

result_scheme<-schema_numerique_ADI(A,C,indice1,indice2,k,h,vitesseh,vitessev,d,r,alpha1,alpha2,MMx,MMy)
A<-result_scheme[[1]]
C<-result_scheme[[2]]

# Affichage des cartes de France pour chaque itération
plot(xs_grid,ys_grid,col=A,main=paste("Day= ",i-deb,sep=''))
plot(nc,add=T)

}


time.final=Sys.time()
print(time.final-time.init)

}
#=======================================================================================================
#============== TEST ===================================================================================
#=======================================================================================================


#===============================================================================================
#==============chargement des donnees dont on dispose===========================================
#===============================================================================================

# Shapefile de la France 
nc <- readShapePoly("Data/france.shp")

x_grid_5km<-read.table("Data/grid_X_5km.csv",header=T)
x_grid_5km<-as.matrix(x_grid_5km)
y_grid_5km<-read.table("Data/grid_Y_5km.csv",header=T)
y_grid_5km<-as.matrix(y_grid_5km)

coord_villes_temp=read.table("Data/coordonnees_parcelles_temp_2000_2011_1.csv",header=T,sep=";")
temperature=read.table("Data/donnees_temp_min_2000_2011_1.csv",header=T,sep=";")

#===============================================================================================
#==============chargement des fonctions dont on dispose=========================================
#===============================================================================================

source("R/realiser_voronoi2.R")
source("R/simulations_diffaphids_schema_numerique_25102012.R")
source("R/affect_val.R")

#=======================================================================================================
#============== TEST ===================================================================================
#=======================================================================================================

diffaphids(5, 1,dd=0.4,vitesse=130,grtype = "bitmap",annee=2000)


