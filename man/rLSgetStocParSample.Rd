\name{rLSgetStocParSample}
\alias{rLSgetStocParSample}

\title{Get a sample object associated with the specified stochastic parameter.}

\description{
 R interface function for LINDO API function \code{LSgetStocParSample}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSgetStocParSample(model,iStv,iRow,jCol)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iStv}{Index of stochastic parameter in the instruction list.}
 \item{iRow}{Row index of the stochastic parameter.}
 \item{jCol}{Column index of the stochastic parameter.}
}

\value{
 If successful, rLSgetStocParSample returns a LINDO API sample object; 
 Otherwise, it returns NULL.
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
