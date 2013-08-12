\name{rLSaddCones}
\alias{rLSaddCones}

\title{Add cones to a given model.}

\description{
 R interface function for LINDO API function \code{LSaddCones}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSaddCones(model,nCone,pszConeTypes,paszConenames = NULL,paiConebegcol,paiConecols)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nCone}{Number of cones to append to the model.}
 \item{pszConeTypes}{A character array containing the type of each cone to be added to the model.}
 \item{paszConenames}{A string array containing the names of each new cone.}
 \item{paiConebegcol}{An integer vector containing the index of the first variable in each new cone.}
 \item{paiConecols}{An integer array containing the indices of the variables in the new cones.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadConeData}}
}

