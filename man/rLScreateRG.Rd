\name{rLScreateRG}
\alias{rLScreateRG}

\title{Create a new instance of LINDO API random generator object.}

\description{
 R interface function for LINDO API function \code{LScreateRG}. For more information,
 please refer to LINDO API User Manual.
}

\details{
 Before this function is called, \code{\link{rLScreateEnv}} must be called to get a valid
 LINDO API environment object.
}

\usage{
rLScreateRG(env,nMethod)
}

\arguments{
 \item{env}{A LINDO API environment object, returned by \code{\link{rLScreateEnv}}.}
 \item{nMethod}{An integer specifying the random number generator to use. Possible values are:
                   \itemize{
                       \item{LS_RANDGEN_FREE}
                       \item{LS_RANDGEN_SYSTEM}
                       \item{LS_RANDGEN_LINDO1}
                       \item{LS_RANDGEN_LINDO2}
                       \item{LS_RANDGEN_LIN1}
                       \item{LS_RANDGEN_MULT1}
                       \item{LS_RANDGEN_MERSENNE}
                   }
               }
}

\value{
 If successful, rLScreateRG returns a LINDO API random generator object; 
 Otherwise, it returns NULL.
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
