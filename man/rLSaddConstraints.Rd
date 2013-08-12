\name{rLSaddConstraints}
\alias{rLSaddConstraints}

\title{Add constraints to a given model.}

\description{
 R interface function for LINDO API function \code{LSaddConstraints}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSaddConstraints(model,nNumaddcons,pszConTypes,paszConNames = NULL,
                    paiArows,padAcoef,paiAcols,padB)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nNumaddcons}{Number of constraints to append.}
 \item{pszConTypes}{A character array containing the type of each constraint to be added to the model.}
 \item{paszConNames}{A string array containing the names of each new constraint.}
 \item{paiArows}{An integer array containing the index of the first nonzero element in each new constraint.}
 \item{padAcoef}{A double array containing the nonzero coefficients of the new constraints.}
 \item{paiAcols}{An integer array containing the column indices of the nonzeros in the new constraints.}
 \item{padB}{A double array containing the right-hand side coefficients for each new constraint.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadLPData}}
\code{\link{rLSaddVariables}}
}

