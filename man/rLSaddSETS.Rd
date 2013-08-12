\name{rLSaddSETS}
\alias{rLSaddSETS}

\title{Add sets to a given model.}

\description{
 R interface function for LINDO API function \code{LSaddSETS}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSaddSETS(model,nSETS,pszSETStype,paiCARDnum,paiSETSbegcol,paiSETScols)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nSETS}{Number of sets to append to the model.}
 \item{pszSETStype}{A character array containing the type of each set to be added to the model.}
 \item{paiCARDnum}{An integer array containing the cardinalities of the sets to be added.}
 \item{paiSETSbegcol}{An integer array containing the index of the first variable in each new set.}
 \item{paiSETScols}{An integer array containing the indices of the variables in the new sets.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadSETSData}}
}

