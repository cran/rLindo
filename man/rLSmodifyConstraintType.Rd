\name{rLSmodifyConstraintType}
\alias{rLSmodifyConstraintType}

\title{Modify the type or direction of a set of constraints.}

\description{
 R interface function for LINDO API function \code{LSmodifyConstraintType}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSmodifyConstraintType(model,nCons,paiCons,pszConTypes)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nCons}{Number of constraint to modify.}
 \item{paiCons}{An integer array containing the indices of the constraints to modify.}
 \item{pszConTypes}{A character array in which each element is either:'L', 'E', 'G' or 'N' indicating each constraint's type.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

