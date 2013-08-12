\name{rLSgetSETSDatai}
\alias{rLSgetSETSDatai}

\title{Retrieve the data for set i from a model data structure.}

\description{
 R interface function for LINDO API function \code{LSgetSETSDatai}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetSETSDatai(model,iSet)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iSet}{The index of the set to retrieve the data for.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pachSETtype}{Set type.}
 \item{piCardnum}{Set cardinality.}
 \item{piNnz}{Number of variables in the set.}
 \item{piVarndx}{An integer array containing the indices of the variables in the set.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetSETSData}}
}