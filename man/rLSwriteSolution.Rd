\name{rLSwriteSolution}
\alias{rLSwriteSolution}

\title{Writes the LP solution to a file.}

\description{
 R interface function for LINDO API function \code{LSwriteSolution}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSwriteSolution(model,pszFname)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFname}{The path and name of the file to which the solution should be written.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
