\name{rLSloadConeData}
\alias{rLSloadConeData}

\title{Load quadratic cone data into a model structure.}

\description{
 R interface function for LINDO API function \code{LSloadConeData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadConeData(model,nCone,pszConeTypes,paiConebegcone,paiConecols)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nCone}{Number of cones to add.}
 \item{pszConeTypes}{A character array containing the type of each cone being added. Valid values for each cone are 'Q' and 'R'.}
 \item{paiConebegcone}{An integer array containing the index of the first variable that appears in the definition of each cone.}
 \item{paiConecols}{An integer array containing the indices of variables representing each cone.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
