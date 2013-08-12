\name{rLSreadVarStartPoint}
\alias{rLSreadVarStartPoint}

\title{Provide initial values for variables from a file.}

\description{
 R interface function for LINDO API function \code{LSreadVarStartPoint}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSreadVarStartPoint(model,pszFname)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFname}{The name of the file from which to read the starting values.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadVarStartPoint}}
}
