\name{rLSgetSETSData}
\alias{rLSgetSETSData}

\title{Retrieve sets data from a model data structure.}

\description{
 R interface function for LINDO API function \code{LSgetSETSData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetSETSData(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{piNsets}{Number of sets in the model.}
 \item{piNtnz}{Total number of variables in the sets.}
 \item{pachSETtype}{A character array containing the type of sets in the model.}
 \item{piCardnum}{An integer array containing the cardinalities of sets in the model.}
 \item{piNnz}{An integer array containing the number of variables in each set in the model.}
 \item{piBegset}{An integer array containing the index of the first variable in each set.}
 \item{piVarndx}{An integer array containing the indices of the variables in the sets.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadSETSData}}
}