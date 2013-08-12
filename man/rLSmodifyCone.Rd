\name{rLSmodifyCone}
\alias{rLSmodifyCone}

\title{Modify the data for the specified cone.}

\description{
 R interface function for LINDO API function \code{LSmodifyCone}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSmodifyCone(model,cConeType,iConeNum,iConeNnz,paiConeCols)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{cConeType}{New type of the cone.}
 \item{iConeNum}{Index of the cone to modify.}
 \item{iConeNnz}{Number of variables characterizing the cone.}
 \item{paiConeCols}{An integer array containing the indices of the variables characterizing the cone.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

