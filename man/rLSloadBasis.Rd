\name{rLSloadBasis}
\alias{rLSloadBasis}

\title{Provide a starting basis for the simplex method.}

\description{
 R interface function for LINDO API function \code{LSloadBasis}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadBasis(model,panCstatus,panRstatus)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{panCstatus}{An integer array containing the status of each column in the given model.
                   Set each variable's element to 0, -1, -2, or -3 for Basic, Nonbasic at
                   lower bound, Nonbasic at upper bound, or Free and nonbasic at zero value, 
                   respectively.}
 \item{panRstatus}{An integer array containing the status of each row in the given model. 
                   Set each row's element to 0 or -1 if row's associated slack variable 
                   is basic or row's associated slack variable is nonbasic at zero, 
                   respectively}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
