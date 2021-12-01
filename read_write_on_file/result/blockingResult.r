library(tidyverse)
library(tibble)
result<-read.csv("result.csv", sep=";") 
result<-tibble(result)
result<-select(result, Size : walltime2) 
  
names(result)[names(result)=="walltime2"]<-"Walltime"
result$Size<-as.factor(result$Size)

result %>%group_by(Size)%>% 
  summarize(Walltime = mean(Walltime, ra.rm=TRUE)/1e-6) -> resultf

resultf$Size <- as.numeric(resultf$Size)

ggplot(resultf,mapping = aes(x=Size,y=Walltime))+
  geom_point()+
  geom_smooth(se=FALSE)+
  labs(x="Number of processors (P)", y= "Runtime in ns", title = "Runtime as a function of processors")+
  theme(plot.title = element_text(hjust = 0.5))
