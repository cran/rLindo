\name{rLSgetLPConstraintDatai}
\alias{rLSgetLPConstraintDatai}

\title{Retrieve the formulation data for a specified constraint in a linear or mixed integer linear program.}

\description{
 R interface function for LINDO API function \code{LSgetLPConstraintDatai}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetLPConstraintDatai(model,iCon)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iCon}{Index of the constraint you wish to receive information on.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pchConType}{Type of the constraint.}
 \item{pdB}{Right-hand side value of the constraint.}
 \item{pnNnz}{Number of nonzero coefficients in the constraint.}
 \item{paiVar}{An integer array containing the indices of the variables with nonzero coefficients in the constraint.}
 \item{padAcoef}{A double array containing the constraint's nonzero coefficients.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetLPVariableDataj}}
}