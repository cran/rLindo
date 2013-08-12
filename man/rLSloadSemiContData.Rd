\name{rLSloadSemiContData}
\alias{rLSloadSemiContData}

\title{Load semi-continuous data into a model structure.}

\description{
 R interface function for LINDO API function \code{LSloadSemiContData}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSloadSemiContData(model,nSCVars,paiVars,padL,padU)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nSCVars}{The number of semi-continuous variables.}
 \item{paiVars}{A integer array containing the indices of semicontinuous variables.}
 \item{padL}{An double array containing the lower bound associated with each semi-continuous variable.}
 \item{padU}{An double array containing the upper bound associated with each semi-continuous variable.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

