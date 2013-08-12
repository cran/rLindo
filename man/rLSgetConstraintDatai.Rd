\name{rLSgetConstraintDatai}
\alias{rLSgetConstraintDatai}

\title{Get data on a specified constraint.}

\description{
 R interface function for LINDO API function \code{LSgetConstraintDatai}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetConstraintDatai(model,iCon)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iCon}{Index of the constraint you wish to receive information on.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pchConType}{Type of the constraint.}
 \item{pchIsNlp}{0 if the constraint is linear and 1 if it is nonlinear.}
 \item{pdB}{Right-hand side value of the constraint.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
