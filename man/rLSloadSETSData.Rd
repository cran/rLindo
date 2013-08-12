\name{rLSloadSETSData}
\alias{rLSloadSETSData}

\title{Load special sets data into a model structure.}

\description{
 R interface function for LINDO API function \code{LSloadSETSData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadSETSData(model,nSETS,pszSETStype,paiCARDnum,paiSETSbegcol,paiSETScols)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nSETS}{Number of sets to load.}
 \item{pszSETStype}{A character array containing the type of each set. Valid values for each cone are \code{LS_MIP_SET_CARD}, \code{LS_MIP_SET_SOS1}, \code{LS_MIP_SET_SOS2}, \code{LS_MIP_SET_SOS3}.}
 \item{paiCARDnum}{An integer array containing set cardinalities.}
 \item{paiSETSbegcol}{An integer array containing the index of the first variable in each set.}
 \item{paiSETScols}{An integer array containing the indices of variables in each set.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

