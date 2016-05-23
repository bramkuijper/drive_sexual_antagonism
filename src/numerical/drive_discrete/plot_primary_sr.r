the.data <- read.table("iter_drive_16_4_2016_202601_818270235",sep=";",header=T)

#the.data <- the.data[the.data$faf < 0.01 | the.data$faf > 0.99,"ssr"] <- NA

the.data[the.data$faf < 0.01 | the.data$faf > 0.99,c("ssr","faf","fxd")] <- NA

pdf("levelplot_secondary_sex_ratio.pdf")
print(
        levelplot(
                ssr ~ tf * tm | h,
                xlab=expression(paste("Cost of expressing ",italic(X)["m"]," in females, ", italic(t)["f"])),
                ylab=expression(paste("Cost of expressing ",italic(X)["f"]," in males, ", italic(t)["m"])),
                main=expression(paste("Secondary sex ratios in the presence of drive and sexual antagonism")),
                data=the.data,
                default.scales=list(arrows=F),
                zlim=c(0,1),
                col.regions=matlab.like(200),
                strip=function(...,strip.levels) { strip.default(...,strip.levels=T) } 
                )
)
dev.off()

pdf("levelplot_xf.pdf")
print(
        levelplot(
                faf ~ tf * tm | h,
                xlab=expression(paste("Cost of expressing ",italic(X)["m"]," in females, ", italic(t)["f"])),
                ylab=expression(paste("Cost of expressing ",italic(X)["f"]," in males, ", italic(t)["m"])),
                main=expression(paste("Frequency of the SA allele ",italic(X)["f"]," (female-benefit), ",italic(p)["f"])),
                data=the.data,
                default.scales=list(arrows=F),
                zlim=c(0,1),
                col.regions=matlab.like(200),
                strip=function(...,strip.levels) { strip.default(...,strip.levels=T) } 
                )
)
dev.off()

pdf("levelplot_drive.pdf")
print(
        levelplot(
                fxd ~ tf * tm | h,
                xlab=expression(paste("Cost of expressing ",italic(X)["m"]," in females, ", italic(t)["f"])),
                ylab=expression(paste("Cost of expressing ",italic(X)["f"]," in males, ", italic(t)["m"])),
                main=expression(paste("Frequency of the drive allele, ",italic(p)["Xd"])),
                data=the.data,
                default.scales=list(arrows=F),
                zlim=c(0,1),
                col.regions=matlab.like(200),
                strip=function(...,strip.levels) { strip.default(...,strip.levels=T) } 
                )
)
dev.off()
