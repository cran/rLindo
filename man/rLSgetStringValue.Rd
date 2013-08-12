\name{rLSgetStringValue}
\alias{rLSgetStringValue}

\title{Retrieve a string value for a specified string index.}

\description{
 R interface function for LINDO API function \code{LSgetStringValue}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSgetStringValue(model,iString)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iString}{The index of the string whose value you wish to retrieve.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdValue}{The string value.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
