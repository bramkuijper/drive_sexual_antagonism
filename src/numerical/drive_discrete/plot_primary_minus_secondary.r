# read in the data
if (!exists("the.data"))
{
    the.data <- read.table("output_relevant.csv",sep=";",header=T)
}

# first provide a global overview of parameter space
# - for a dataset with a certain recombination rate,
# - where there is a cost of drive in both sexes
# - cost of drive is higher in males than females
pdf("psrminssr_vary_cm_cf",width=25,height=20)
print(
        contourplot(
                        (ssr - psr) ~ tf * tm | h * kdrive * cf * cm, 
                        data=the.data[the.data$r == 0.4 & the.data$cm > 0 & the.data$cf > 0 & the.data$cm > the.data$cf,],
                        ylim=c(0,1),
                        xlim=c(0,1),
                        region=T,
                        col.regions=matlab.like,
                        strip=function(strip.levels,...) { strip.default(strip.levels=T,...) }
                    )
)
dev.off()

# then a close-up of some of the space:
pdf("psrminssr_example",width=25,height=20)
print(
        contourplot(
                        (ssr - psr) ~ tf * tm | h * kdrive * cf * cm, 
                        data=the.data[the.data$r == 0.4 & the.data$cm > 0 & the.data$cf > 0 & the.data$cm > the.data$cf,],
                        ylim=c(0,1),
                        xlim=c(0,1),
                        region=T,
                        col.regions=matlab.like,
                        strip=function(strip.levels,...) { strip.default(strip.levels=T,...) }
                    )
)
dev.off()

